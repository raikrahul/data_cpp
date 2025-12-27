/*
 * DEMO 02: EXTRACT PAGE TABLE INDICES
 * ════════════════════════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input: 48-bit Virtual Address (e.g., 0x7FFE_5E4E_D123).
 *    Action: Slice into 4 indices + 1 offset.
 *    Output: 9 | 9 | 9 | 9 | 12 bits.
 *
 *    Computation (0x7FFE5E4ED123):
 *    PML4 = (VA >> 39) & 0x1FF = 0xFF  = 255.
 *    PDPT = (VA >> 30) & 0x1FF = 0x1FF = 511.
 *    PD   = (VA >> 21) & 0x1FF = 0x127 = 295.
 *    PT   = (VA >> 12) & 0x1FF = 0x0ED = 237.
 *    OFF  = VA & 0xFFF         = 0x123 = 291.
 *
 * 2. WHY:
 *    - To navigate the distinct levels of the Page Table Tree.
 *    - Level 4 (PML4) selects 512GB region.
 *    - Level 3 (PDPT) selects 1GB region.
 *    - Level 2 (PD)   selects 2MB region.
 *    - Level 1 (PT)   selects 4KB Page.
 *
 * 3. WHERE:
 *    - In the Virtual Address bits themselves.
 *    - It's a "Path" encoded in the address.
 *
 * 4. WHO:
 *    - MMU: Hardware splitter.
 *    - Developer: Debugging mappings.
 *
 * 5. WHEN:
 *    - Address Translation time.
 *
 * 6. WITHOUT:
 *    - Linear search of 256TB space? Impossible.
 *    - Hash Table? Collisions/O(1) issues.
 *    - Radix Tree (Page Table) is deterministic.
 *
 * 7. WHICH:
 *    - Bits 47:39 -> Index 4.
 *    - Bits 38:30 -> Index 3.
 *    - Bits 29:21 -> Index 2.
 *    - Bits 20:12 -> Index 1.
 *    - Bits 11:00 -> Offset.
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: Calendar Date
 * - Date Integer: 20241227 (YYYYMMDD).
 * - Format: Fixed-width (4 digits, 2 digits, 2 digits).
 *
 * Extraction:
 * - Year  = Date / 10000       = 2024.
 * - Month = (Date / 100) % 100 = 12.
 * - Day   = Date % 100         = 27.
 *
 * Contradiction:
 * - A "Month" of 99 would be invalid.
 * - Page indices map to 0-511.
 * - If index > 511? Impossible with 9 bits.
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 02: Extract Page Table Indices");

/* Test VAs from your machine */
static unsigned long test_vaddrs[] = {
    0x7FFE5E4ED123UL,     /* your process_a stack */
    0xFFFF89DF00000000UL, /* your page_offset_base */
    0x0000000000001000UL, /* minimal user VA */
    0xFFFFFFFFFFFFFFFFUL, /* max kernel VA */
};
#define NUM_VADDRS (sizeof(test_vaddrs) / sizeof(test_vaddrs[0]))

/*
 * Extract and display indices with full calculation trace
 */
static void show_extraction(struct seq_file* m, unsigned long va) {
    unsigned long pml4, pdpt, pd, pt, off;
    unsigned long shifted;

    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "VA = 0x%016lx\n", va);
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    /* PML4: bits [47:39] */
    shifted = va >> 39;
    pml4 = shifted & 0x1FF;
    seq_printf(m, "PML4: 0x%lx >> 39 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pml4);

    /* PDPT: bits [38:30] */
    shifted = va >> 30;
    pdpt = shifted & 0x1FF;
    seq_printf(m, "PDPT: 0x%lx >> 30 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pdpt);

    /* PD: bits [29:21] */
    shifted = va >> 21;
    pd = shifted & 0x1FF;
    seq_printf(m, "PD:   0x%lx >> 21 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pd);

    /* PT: bits [20:12] */
    shifted = va >> 12;
    pt = shifted & 0x1FF;
    seq_printf(m, "PT:   0x%lx >> 12 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pt);

    /* Offset: bits [11:0] */
    off = va & 0xFFF;
    seq_printf(m, "OFF:  0x%lx & 0xFFF = %lu (0x%lx)\n\n", va, off, off);
}

static int indices_show(struct seq_file* m, void* v) {
    int i;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 02: PAGE TABLE INDEX EXTRACTION\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "FORMULA:\n");
    seq_printf(m, "  PML4 = (VA >> 39) & 0x1FF\n");
    seq_printf(m, "  PDPT = (VA >> 30) & 0x1FF\n");
    seq_printf(m, "  PD   = (VA >> 21) & 0x1FF\n");
    seq_printf(m, "  PT   = (VA >> 12) & 0x1FF\n");
    seq_printf(m, "  OFF  = VA & 0xFFF\n\n");

    for (i = 0; i < NUM_VADDRS; i++) {
        show_extraction(m, test_vaddrs[i]);
    }

    return 0;
}

static int indices_open(struct inode* inode, struct file* file) {
    return single_open(file, indices_show, NULL);
}

static const struct proc_ops indices_ops = {
    .proc_open = indices_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init indices_init(void) {
    proc_create("demo_indices", 0444, NULL, &indices_ops);
    pr_info("demo_indices: loaded\n");
    return 0;
}

static void __exit indices_exit(void) {
    remove_proc_entry("demo_indices", NULL);
    pr_info("demo_indices: unloaded\n");
}

module_init(indices_init);
module_exit(indices_exit);
