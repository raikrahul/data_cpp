/*
 * DEMO 01: READ CR3 REGISTER
 * ══════════════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input: CPU Register CR3.
 *    Action: Read 64-bit value.
 *    Output: Physical Base Address of the current Page Table.
 *
 *    Computation:
 *    CR3_Value = 0x0000_0001_337A_3000 (Example)
 *    PML4_Base = CR3_Value & 0x000FFFFFFFFFF000
 *
 * 2. WHY:
 *    - The MMU needs a root for the translation tree.
 *    - Cannot search entire RAM for Page Tables.
 *    - CR3 is the anchored pointer.
 *
 * 3. WHERE:
 *    - Inside the CPU Core (Control Register 3).
 *    - Not in RAM.
 *
 * 4. WHO:
 *    - Hardware: Uses it for every Fetch/Load/Store.
 *    - OS: Updates it during Context Switch (`switch_mm`).
 *
 * 5. WHEN:
 *    - System Boot (Initial CR3).
 *    - Process Creation (New CR3).
 *    - Context Switch (Load CR3).
 *
 * 6. WITHOUT:
 *    - CPU would not know Virtual-to-Physical mapping.
 *    - No Virtual Memory.
 *    - Real Mode (16-bit) or Flat Mode only.
 *
 * 7. WHICH:
 *    - CR3[Bit 63:52]: Reserved/Protection Keys.
 *    - CR3[Bit 51:12]: Physical Address Frame (40 bits).
 *    - CR3[Bit 11:00]: PCID (Process Context ID) / Flags.
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: Library Master Index
 * - Library has 1 Million Books.
 * - Books are scattered randomly.
 * - MASTER INDEX matches Title -> Location.
 * - The Master Index is a Book itself.
 * - Where is the Master Index?
 *
 * Solution:
 * - A small yellow note (CR3) on the Librarian's Desk.
 * - Note says: "Master Index is at Aisle 4, Shelf 2".
 *
 * Logic:
 * - Without the Note (CR3), you cannot find the Index (PML4).
 * - Without the Index, you cannot find the Books (Pages).
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 01: Read CR3");

extern unsigned long page_offset_base;

#define CR3_ADDR_MASK 0x000FFFFFFFFFF000UL

static unsigned long read_cr3_value(void) {
    unsigned long cr3;
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    return cr3;
}

static int demo_cr3_show(struct seq_file* m, void* v) {
    unsigned long cr3_raw, cr3_addr, cr3_pcid;
    unsigned long pml4_virt;
    int bits_used;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 01: READ CR3 REGISTER\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    /* 1. Read Raw Value */
    cr3_raw = read_cr3_value();
    seq_printf(m, "1. RAW CR3 VALUE:\n");
    seq_printf(m, "   0x%016lx\n", cr3_raw);
    seq_printf(m, "   (Binary: ...%lu...)\n\n", cr3_raw & 0xFFF); /* Show low bits */

    /* 2. Decode Components */
    cr3_addr = cr3_raw & CR3_ADDR_MASK;
    cr3_pcid = cr3_raw & 0xFFF;

    seq_printf(m, "2. DECODED COMPONENTS:\n");
    seq_printf(m, "   Physical Base (PML4) = 0x%016lx\n", cr3_addr);
    seq_printf(m, "   PCID / Flags         = 0x%03lx\n\n", cr3_pcid);

    /* 3. Axiomatic Check */
    bits_used = fls64(cr3_addr);
    seq_printf(m, "3. AXIOMATIC CHECKS:\n");
    seq_printf(m, "   Max Physical Address Bit: %d\n", bits_used);
    seq_printf(m, "   Expected range: 12..52 (Architecture dependent)\n");
    seq_printf(m, "   Is Aligned (Low 12 bits 0)? %s\n\n", (cr3_addr & 0xFFF) == 0 ? "YES" : "NO");

    /* 4. Derive Virtual Address */
    pml4_virt = (unsigned long)__va(cr3_addr);
    seq_printf(m, "4. DERIVED VIRTUAL ADDRESS:\n");
    seq_printf(m, "   phys_to_virt(0x%lx)\n", cr3_addr);
    seq_printf(m, "   = page_offset_base + phys\n");
    seq_printf(m, "   = 0x%lx + 0x%lx\n", page_offset_base, cr3_addr);
    seq_printf(m, "   = 0x%016lx\n", pml4_virt);

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
    pr_info("demo_cr3: loaded\n");
    return 0;
}

static void __exit demo_cr3_exit(void) {
    remove_proc_entry("demo_cr3", NULL);
    pr_info("demo_cr3: unloaded\n");
}

module_init(demo_cr3_init);
module_exit(demo_cr3_exit);
