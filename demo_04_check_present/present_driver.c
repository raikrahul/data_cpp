/*
 * DEMO 04: CHECK PRESENT BIT
 * ══════════════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input:  Entry = 0x80000002FAE00067
 *    Action: Check Bit 0 (LSB)
 *    Output: 1 (Present) or 0 (Not Present)
 *
 *    Calculation:
 *    0x80000002FAE00067 (hex)
 *    Bin: 1000...0010_1111_1010_1110_0000_0000_0000_0110_0111
 *                                                       ^
 *                                                       LSB is 1
 *    0x67 = 0110_0111
 *    0x67 & 0x01 = 0x01 (True)
 *
 * 2. WHY:
 *    - RAM is limited (16GB). Virtual Space is huge (256TB).
 *    - Not all Virtual pages can be in Physical RAM.
 *    - We need a marker: "Is this page in RAM right now?"
 *    - Bit 0 = 0 → Page is on Disk (Swap) or Invalid.
 *    - Bit 0 = 1 → Page is in RAM.
 *
 * 3. WHERE:
 *    - Bit 0 of the 64-bit Page Table Entry.
 *    - Located at physical address derived in Demo 03.
 *
 * 4. WHO:
 *    - MMU (Hardware): Checks this bit *before* reading any other bit.
 *    - If 0, MMU raises Exception #14 (Page Fault).
 *    - If 1, MMU proceeds to check R/W, U/S, etc.
 *
 * 5. WHEN:
 *    - Every single memory access (read or write).
 *    - Example: `MOV RAX, [0xADDR]` triggers check.
 *
 * 6. WITHOUT:
 *    - If Bit 0 didn't exist:
 *    - CPU would assume address 0x0 is valid.
 *    - Or CPU would assume invalid address points to random RAM.
 *    - Result: Corruption or Security Hole.
 *
 * 7. WHICH:
 *    - Bit 0 only.
 *    - Bits 1-63 are ignored by MMU if Bit 0 is 0 (mostly).
 *    - (OS uses bits 1-63 for swap location if P=0).
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: Office Building Directions
 * - Directory lists 512 Employee Names.
 * - Next to name: Room Number (Address).
 * - BUT: Employee might be "Out of Office".
 *
 * Input:
 * - Entry: "Smith | Room 302 | Present: No"
 *
 * Action:
 * - Visitor checks "Present" column FIRST.
 * - If "No", ignores "Room 302" (might be stale).
 * - Goes to Reception (Page Fault Handler).
 *
 * Numerical Analogy:
 * - Entry = 3020 (decimal)
 * - If even (ends in 0) -> Out.
 * - If odd (ends in 1) -> In.
 * - 3020 / 2 = 1510 remainder 0 -> Out.
 * - 3021 / 2 = 1510 remainder 1 -> In.
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 04: Check Present Bit");

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL

static int is_present(unsigned long entry) {
    /* entry & 1 = extract bit 0 */
    return (entry & 1) ? 1 : 0;
}

static void decode_flags(struct seq_file* m, unsigned long entry) {
    seq_printf(m, "  bit 0 (P):   %lu → %s\n", entry & 1, (entry & 1) ? "Present" : "Not Present");
    seq_printf(m, "  bit 1 (RW):  %lu → %s\n", (entry >> 1) & 1,
               ((entry >> 1) & 1) ? "Writable" : "Read-only");
    seq_printf(m, "  bit 2 (US):  %lu → %s\n", (entry >> 2) & 1,
               ((entry >> 2) & 1) ? "User" : "Kernel");
    seq_printf(m, "  bit 5 (A):   %lu → %s\n", (entry >> 5) & 1,
               ((entry >> 5) & 1) ? "Accessed" : "Not accessed");
    seq_printf(m, "  bit 6 (D):   %lu → %s\n", (entry >> 6) & 1,
               ((entry >> 6) & 1) ? "Dirty" : "Clean");
    seq_printf(m, "  bit 7 (PS):  %lu → %s\n", (entry >> 7) & 1,
               ((entry >> 7) & 1) ? "Huge Page" : "Table");
    seq_printf(m, "  bit 63 (NX): %lu → %s\n", (entry >> 63) & 1,
               ((entry >> 63) & 1) ? "No Execute" : "Executable");
}

static int demo_present_show(struct seq_file* m, void* v) {
    unsigned long cr3, pml4_phys;
    unsigned long* pml4_virt;
    unsigned long entry;
    int i;
    int present_count = 0;

    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    pml4_phys = cr3 & PTE_ADDR_MASK;
    pml4_virt = (unsigned long*)__va(pml4_phys);

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 04: CHECK PRESENT BIT\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "FORMULA: is_present = entry & 1\n\n");

    /* Count present entries */
    for (i = 0; i < 512; i++) {
        if (pml4_virt[i] & 1) present_count++;
    }
    seq_printf(m, "PML4 entries present: %d / 512\n\n", present_count);

    /* Show user space entries */
    seq_printf(m, "USER SPACE (0-255):\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    for (i = 0; i < 256; i++) {
        entry = pml4_virt[i];
        if (entry & 1) {
            seq_printf(m, "PML4[%d] = 0x%016lx\n", i, entry);
            decode_flags(m, entry);
            seq_printf(m, "\n");
        }
    }

    return 0;
}

static int demo_present_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_present_show, NULL);
}

static const struct proc_ops demo_present_ops = {
    .proc_open = demo_present_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_present_init(void) {
    proc_create("demo_present", 0444, NULL, &demo_present_ops);
    pr_info("demo_present: loaded\n");
    return 0;
}

static void __exit demo_present_exit(void) { remove_proc_entry("demo_present", NULL); }

module_init(demo_present_init);
module_exit(demo_present_exit);
