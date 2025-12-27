/*
 * DEMO 08: 2MB HUGE PAGE WALK
 * ═══════════════════════════
 *
 * Walk stops at PD level when PS=1
 * Offset = 21 bits instead of 12
 *
 * DIRECT MAP USES 2MB PAGES:
 *   page_offset_base = 0xFFFF89DF00000000
 *   Walk this address → should see PS=1 at PD level
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 08: 2MB Huge Page Walk");

extern unsigned long page_offset_base;

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL
#define HUGE_2MB_MASK 0x000FFFFFFFE00000UL

static int demo_walk2mb_show(struct seq_file* m, void* v) {
    unsigned long va, cr3, table_phys, entry;
    unsigned long pml4_idx, pdpt_idx, pd_idx;

    /* Use page_offset_base as test VA (direct map uses 2MB pages) */
    va = page_offset_base;

    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    table_phys = cr3 & PTE_ADDR_MASK;

    pml4_idx = (va >> 39) & 0x1FF;
    pdpt_idx = (va >> 30) & 0x1FF;
    pd_idx = (va >> 21) & 0x1FF;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 08: 2MB HUGE PAGE WALK\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "VA = 0x%lx (page_offset_base)\n", va);
    seq_printf(m, "PML4=%lu PDPT=%lu PD=%lu\n\n", pml4_idx, pdpt_idx, pd_idx);

    /* L4: PML4 */
    entry = ((unsigned long*)__va(table_phys))[pml4_idx];
    seq_printf(m, "L4 PML4[%lu] = 0x%016lx\n", pml4_idx, entry);
    if (!(entry & 1)) {
        seq_printf(m, "  NOT PRESENT\n");
        return 0;
    }
    table_phys = entry & PTE_ADDR_MASK;
    seq_printf(m, "  → PDPT @ 0x%lx\n\n", table_phys);

    /* L3: PDPT */
    entry = ((unsigned long*)__va(table_phys))[pdpt_idx];
    seq_printf(m, "L3 PDPT[%lu] = 0x%016lx\n", pdpt_idx, entry);
    if (!(entry & 1)) {
        seq_printf(m, "  NOT PRESENT\n");
        return 0;
    }
    if ((entry >> 7) & 1) {
        seq_printf(m, "  PS=1 → 1GB HUGE (unexpected)\n");
        return 0;
    }
    table_phys = entry & PTE_ADDR_MASK;
    seq_printf(m, "  PS=0 → PD @ 0x%lx\n\n", table_phys);

    /* L2: PD - expect huge page here */
    entry = ((unsigned long*)__va(table_phys))[pd_idx];
    seq_printf(m, "L2 PD[%lu] = 0x%016lx\n", pd_idx, entry);
    if (!(entry & 1)) {
        seq_printf(m, "  NOT PRESENT\n");
        return 0;
    }

    unsigned long ps_bit = (entry >> 7) & 1;
    seq_printf(m, "  bit 7 = (0x%lx >> 7) & 1 = %lu\n", entry, ps_bit);

    if (ps_bit) {
        unsigned long page_base = entry & HUGE_2MB_MASK;
        unsigned long offset_21 = va & 0x1FFFFF;
        unsigned long final_phys = page_base | offset_21;

        seq_printf(m, "  PS=1 → 2MB HUGE PAGE ✓\n\n");
        seq_printf(m, "CALCULATION:\n");
        seq_printf(m, "  page_base = entry & 0x%lx = 0x%lx\n", HUGE_2MB_MASK, page_base);
        seq_printf(m, "  offset = VA & 0x1FFFFF = 0x%lx\n", offset_21);
        seq_printf(m, "  final_phys = 0x%lx | 0x%lx = 0x%lx\n", page_base, offset_21, final_phys);
        seq_printf(m, "\nLEVELS TRAVERSED: 3 (PML4 → PDPT → PD)\n");
        seq_printf(m, "RAM READS: 3 × 8 = 24 bytes\n");
    } else {
        seq_printf(m, "  PS=0 → Not a 2MB huge page, would continue to PT\n");
    }

    return 0;
}

static int demo_walk2mb_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_walk2mb_show, NULL);
}

static const struct proc_ops demo_walk2mb_ops = {
    .proc_open = demo_walk2mb_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_walk2mb_init(void) {
    proc_create("demo_walk2mb", 0444, NULL, &demo_walk2mb_ops);
    pr_info("demo_walk2mb: loaded\n");
    return 0;
}

static void __exit demo_walk2mb_exit(void) { remove_proc_entry("demo_walk2mb", NULL); }

module_init(demo_walk2mb_init);
module_exit(demo_walk2mb_exit);
