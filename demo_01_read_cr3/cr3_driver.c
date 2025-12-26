/*
 * DEMO 01: READ CR3 REGISTER
 * ==========================
 *
 * WHAT THIS DRIVER DOES:
 * Reads the CR3 control register and outputs its components to /proc/demo_cr3
 *
 * YOUR MACHINE DATA:
 * CPU: AMD Ryzen 5 4600H
 * CR3 observed values: 0x2CCB6C000, 0x12EB28000, 0x1337A3000, 0x10AB4A000
 * All end in 0x000 (4KB aligned, low 12 bits = 0)
 *
 * CR3 BIT LAYOUT (64 bits):
 * ┌────────────────┬────────────────────────────────────────┬────────────────┐
 * │ bits [63:52]   │ bits [51:12]                           │ bits [11:0]    │
 * │ 12 bits        │ 40 bits                                │ 12 bits        │
 * │ RESERVED = 0   │ PML4 PHYSICAL ADDRESS                  │ PCID (Intel)   │
 * │                │                                        │ Reserved (AMD) │
 * └────────────────┴────────────────────────────────────────┴────────────────┘
 *
 * EXAMPLE WITH YOUR CR3 = 0x1337A3000:
 *   Full value:     0x00000001337A3000
 *   bits [63:52]:   0x000 (reserved, always 0)
 *   bits [51:12]:   0x1337A3 (40-bit field, only 21 bits used = 0x1337A3)
 *   bits [11:0]:    0x000 (PCID on Intel, reserved on AMD)
 *
 *   PML4 physical = 0x1337A3 × 0x1000 = 0x1337A3000
 *
 *   CALCULATION:
 *   0x1337A3 = 1,259,427 (decimal)
 *   1,259,427 × 4,096 = 5,158,772,736 = 0x1337A3000 ✓
 *
 *   log2(0x1337A3000) = log2(5,158,772,736) = 32.26
 *   → 33 bits needed to represent this address
 *   → Stored as 21 bits (after removing low 12 zeros)
 *
 * WHY CR3 CHANGES:
 *   Each process has its own PML4 table at different physical address.
 *   Context switch → CPU loads new CR3 → new address space.
 *
 *   process_a: CR3 = 0x2CCB6C000
 *   process_b: CR3 = 0x12EB28000
 *   shell:     CR3 = 0x1337A3000
 *
 *   KERNEL HALF (PML4[256:511]) same in all → shared kernel mappings
 *   USER HALF (PML4[0:255]) different → each process has own user space
 *
 * INSTRUCTION USED:
 *   asm volatile("mov %%cr3, %0" : "=r"(cr3));
 *
 *   mov %%cr3, %0:
 *   - %%cr3: CR3 register (double % for AT&T syntax in inline asm)
 *   - %0: first output operand (the C variable 'cr3')
 *   - "=r": constraint = output (=) to any register (r)
 *
 *   volatile: don't optimize away, always execute
 *
 * RING 0 ONLY:
 *   CR3 is privileged. User space (ring 3) cannot read it.
 *   Attempt → #GP (General Protection) fault → SIGSEGV.
 *   Kernel modules run in ring 0 → can read CR3.
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 01: Read CR3 Register");

/*
 * MASK TO EXTRACT PML4 PHYSICAL ADDRESS:
 *
 * 0x000FFFFFFFFFF000 = bits [51:12] = 40 ones shifted left by 12
 *
 * Binary: 0000_0000_0000_1111_1111_1111_1111_1111_1111_1111_1111_1111_0000_0000_0000
 *         ^^^^^^^^^^^^^^^                                          ^^^^^^^^^^^^
 *         bits [63:52]=0                                           bits [11:0]=0
 *                       ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *                       bits [51:12] = where address lives
 *
 * WHY NOT 0xFFFFFFFFFFFFF000?
 *   Bits [63:52] are reserved/NX. Must clear them.
 *   Intel and AMD reserve these bits differently.
 *   0x000FFFFFFFFFF000 is safe for both.
 */
#define CR3_ADDR_MASK 0x000FFFFFFFFFF000UL

/*
 * read_cr3_value:
 *
 * Reads CR3 using inline assembly.
 *
 * MEMORY LAYOUT DURING CALL:
 *   Stack at some address S:
 *   [S+0]: return address (8 bytes)
 *   [S-8]: local variable 'cr3' (8 bytes) ← result stored here
 *
 * INSTRUCTION EXECUTION:
 *   1. CPU fetches "mov cr3, rax" (or whatever register GCC picks)
 *   2. CPU reads 64-bit CR3 value from internal register
 *   3. CPU writes value to chosen general-purpose register
 *   4. Compiler-generated code moves register to 'cr3' variable on stack
 *
 * TIMING:
 *   mov cr3, reg takes ~5-20 cycles
 *   Much faster than memory access
 */
static unsigned long read_cr3_value(void) {
    unsigned long cr3;
    /*
     * Inline assembly breakdown:
     *
     * "mov %%cr3, %0"  → assembly template
     *     mov         → instruction
     *     %%cr3       → source (CR3 register, %% escapes % for AT&T)
     *     %0          → destination (first operand, which is 'cr3')
     *
     * : "=r"(cr3)     → output operand list
     *     =           → write-only (output)
     *     r           → any general-purpose register
     *     (cr3)       → C variable to store result
     *
     * No input operands (nothing after second :)
     * No clobbers (nothing after third :)
     */
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    return cr3;
}

/*
 * demo_cr3_show:
 *
 * Called when user reads /proc/demo_cr3
 *
 * seq_file interface:
 *   - Kernel allocates buffer
 *   - seq_printf writes to buffer
 *   - Kernel copies buffer to user space
 *   - Handles large output by chunking automatically
 */
static int demo_cr3_show(struct seq_file* m, void* v) {
    unsigned long cr3_raw, cr3_addr, cr3_pcid;
    unsigned long pml4_virt;
    int bits_used;

    /* Read current CR3 */
    cr3_raw = read_cr3_value();

    /*
     * EXTRACT COMPONENTS:
     *
     * Example: CR3 = 0x00000001337A3000
     *
     * cr3_addr = 0x1337A3000 & 0x000FFFFFFFFFF000 = 0x1337A3000
     *   → PML4 physical address
     *
     * cr3_pcid = 0x1337A3000 & 0xFFF = 0x000
     *   → PCID (Process Context ID)
     *   → AMD Ryzen: always 0 (no PCID)
     *   → Intel with PCID: 0-4095
     */
    cr3_addr = cr3_raw & CR3_ADDR_MASK;
    cr3_pcid = cr3_raw & 0xFFF;

    /*
     * CALCULATE BITS USED:
     *
     * fls = "find last set" = position of highest set bit + 1
     *
     * Example: cr3_addr = 0x1337A3000 = 5,158,772,736
     * Binary: 1_0011_0011_0111_1010_0011_0000_0000_0000
     *         ^
     *         bit 32 is highest set bit
     *
     * fls64(0x1337A3000) = 33
     *
     * Meaning: 33 bits needed to represent this address
     */
    bits_used = fls64(cr3_addr);

    /*
     * CALCULATE VIRTUAL ADDRESS OF PML4:
     *
     * page_offset_base = 0xFFFF89DF00000000 (your machine, KASLR randomized)
     *
     * pml4_virt = page_offset_base + cr3_addr
     *           = 0xFFFF89DF00000000 + 0x1337A3000
     *           = 0xFFFF89E0337A3000
     *
     * This is the kernel virtual address you can dereference to read PML4.
     */
    pml4_virt = (unsigned long)__va(cr3_addr);

    seq_printf(m, "═══════════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 01: CR3 REGISTER\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "CR3_RAW:        0x%016lx\n", cr3_raw);
    seq_printf(m, "CR3_ADDR:       0x%lx (bits [51:12])\n", cr3_addr);
    seq_printf(m, "CR3_PCID:       0x%03lx (bits [11:0])\n", cr3_pcid);
    seq_printf(m, "BITS_USED:      %d bits\n\n", bits_used);

    seq_printf(m, "CALCULATION:\n");
    seq_printf(m, "  PML4_PHYS = CR3 & 0x000FFFFFFFFFF000\n");
    seq_printf(m, "            = 0x%016lx & 0x000FFFFFFFFFF000\n", cr3_raw);
    seq_printf(m, "            = 0x%lx\n\n", cr3_addr);

    seq_printf(m, "VIRTUAL ADDRESS (via __va):\n");
    seq_printf(m, "  page_offset_base + 0x%lx = 0x%lx\n\n", cr3_addr, pml4_virt);

    seq_printf(m, "PML4 TABLE:\n");
    seq_printf(m, "  Physical: 0x%lx to 0x%lx (4096 bytes)\n", cr3_addr, cr3_addr + 4095);
    seq_printf(m, "  Entries:  512 × 8 bytes = 4096 bytes\n");
    seq_printf(m, "  Range:    PML4[0] to PML4[511]\n\n");

    seq_printf(m, "MEANING:\n");
    seq_printf(m, "  This CR3 belongs to the process reading /proc/demo_cr3\n");
    seq_printf(m, "  Each process has different CR3 (different PML4 table)\n");
    seq_printf(m, "  Context switch → load new CR3 → new address space\n");

    return 0;
}

static int demo_cr3_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_cr3_show, NULL);
}

static const struct proc_ops demo_cr3_ops = {
    .proc_open = demo_cr3_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_cr3_init(void) {
    proc_create("demo_cr3", 0444, NULL, &demo_cr3_ops);
    pr_info("demo_cr3: module loaded. Read /proc/demo_cr3\n");
    return 0;
}

static void __exit demo_cr3_exit(void) {
    remove_proc_entry("demo_cr3", NULL);
    pr_info("demo_cr3: module unloaded\n");
}

module_init(demo_cr3_init);
module_exit(demo_cr3_exit);
