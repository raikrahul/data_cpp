/*
 * DEMO 01: READ CR3 REGISTER
 * ==========================
 *
 * ═══════════════════════════════════════════════════════════════════════════
 * AXIOMATIC DERIVATION - EVERY CLAIM PROVEN FROM FIRST PRINCIPLES
 * ═══════════════════════════════════════════════════════════════════════════
 *
 * AXIOM 1: YOUR CPU HAS 44 PHYSICAL ADDRESS BITS
 * ──────────────────────────────────────────────
 * Source: cat /proc/cpuinfo | grep "address sizes"
 * Output: "address sizes : 44 bits physical, 48 bits virtual"
 *
 * DERIVATION:
 *   44 bits → max addressable = 2^44 bytes
 *   2^44 = 2^10 × 2^10 × 2^10 × 2^10 × 2^4
 *        = 1024 × 1024 × 1024 × 1024 × 16
 *        = 17,592,186,044,416 bytes
 *        = 16 TB
 *   ∴ Your CPU can address up to 16 TB of physical RAM
 *   ∴ Your 15 GB RAM uses only ~34 bits (log2(16,000,000,000) = 33.9)
 *
 * AXIOM 2: CR3 STORES PHYSICAL ADDRESS IN BITS [51:12]
 * ────────────────────────────────────────────────────
 * Source: Intel SDM Volume 3, Chapter 4.5 "CR3"
 *
 * DERIVATION:
 *   bits [51:12] = 40 bits for address
 *   bits [11:0]  = 12 bits for PCID (Intel) or reserved (AMD)
 *   bits [63:52] = 12 bits reserved
 *
 *   Why 40 bits for address?
 *     40 bits can address 2^40 = 1 TB of 4KB pages
 *     Each PML4 table is 4KB = 2^12 bytes
 *     So address stored is (physical / 4096), then shifted left 12
 *     Effectively stores physical address with last 12 bits = 0 (4KB aligned)
 *
 * AXIOM 3: CR3 FROM YOUR MACHINE
 * ─────────────────────────────
 * Source: cat /proc/pagewalk (from existing kernel module)
 * Output: CR3=0x00000001337A3000
 *
 * DERIVATION:
 *   0x1337A3000 in binary:
 *   0001_0011_0011_0111_1010_0011_0000_0000_0000
 *
 *   bit 32: 1 (highest set bit)
 *   bits [31:0]: 0x337A3000
 *
 *   fls64(0x1337A3000) = 33 → 33 bits needed
 *
 *   Alignment check:
 *   0x1337A3000 & 0xFFF = 0x000 ✓ (4KB aligned)
 *
 * AXIOM 4: PAGE_OFFSET_BASE ON YOUR MACHINE
 * ─────────────────────────────────────────
 * Source: sudo cat /proc/kallsyms | grep page_offset_base
 * Output: ffffffff9695b668 D page_offset_base
 * Value: 0xFFFF89DF00000000 (read from prove_direct_map.ko)
 *
 * DERIVATION:
 *   To read physical 0x1337A3000 in kernel code:
 *   virtual = page_offset_base + physical
 *           = 0xFFFF89DF00000000 + 0x1337A3000
 *
 *   Step by step:
 *   0xFFFF89DF00000000
 * +        0x1337A3000
 *   ─────────────────
 *   0xFFFF89E0337A3000
 *
 *   Verify (hex addition):
 *   ...DF00000000 + 1337A3000:
 *   Low 8 hex: 00000000 + 337A3000 = 337A3000
 *   Next hex:  DF + 1 (carry) = E0
 *   Result: 0xFFFF89E0337A3000 ✓
 *
 * AXIOM 5: WHY MASK IS 0x000FFFFFFFFFF000
 * ──────────────────────────────────────
 * Need to extract bits [51:12] from CR3.
 *
 * DERIVATION:
 *   bits [11:0]  = 0 → mask has 0s in positions 0-11
 *   bits [51:12] = 1 → mask has 1s in positions 12-51
 *   bits [63:52] = 0 → mask has 0s in positions 52-63
 *
 *   bits [51:12] = 40 ones starting at bit 12
 *   = (2^40 - 1) << 12
 *   = 0xFFFFFFFFFF << 12
 *   = 0xFFFFFFFFFF000
 *
 *   But we also need to clear bits [63:52]:
 *   0x000FFFFFFFFFF000
 *
 *   Verify: count Fs
 *   0x000 (3 hex = 12 bits zeros at top)
 *   FFFFFFFFFF (10 Fs = 40 bits ones)
 *   000 (3 hex = 12 bits zeros at bottom)
 *   Total: 12 + 40 + 12 = 64 bits ✓
 *
 * AXIOM 6: PML4 TABLE SIZE = 4096 BYTES
 * ────────────────────────────────────
 * Source: Intel SDM Volume 3, Chapter 4.5
 *
 * DERIVATION:
 *   PML4 has 512 entries (x86_64 specification)
 *   Each entry is 8 bytes (64 bits)
 *   512 × 8 = 4096 bytes = 4 KB = 1 page
 *
 *   Why 512?
 *   9 bits of virtual address select PML4 entry
 *   2^9 = 512 ✓
 *
 * ═══════════════════════════════════════════════════════════════════════════
 * OBSERVED CR3 VALUES FROM YOUR MACHINE
 * ═══════════════════════════════════════════════════════════════════════════
 *
 * process_a:     CR3 = 0x2CCB6C000   (PID varies)
 * process_b:     CR3 = 0x12EB28000   (PID varies)
 * shell:         CR3 = 0x1337A3000   (bash)
 * pagewalk_proc: CR3 = 0x10AB4A000   (cat reading /proc)
 *
 * OBSERVATION: All end in 0x000 (low 12 bits = 0)
 * REASON: 4KB alignment requirement for PML4 table
 *
 * OBSERVATION: Different processes have different CR3
 * REASON: Each process has its own PML4 table
 *
 * OBSERVATION: Range 0x10AB4A000 to 0x2CCB6C000 (~4.6 GB spread)
 * REASON: PML4 tables allocated from Normal zone (4GB+) of RAM
 *
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
