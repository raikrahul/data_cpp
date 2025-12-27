/*
 * DEMO 07: FULL 4KB PAGE WALK
 * ═══════════════════════════
 *
 * Walk 4 levels: PML4 → PDPT → PD → PT → 4KB page
 * Each level: check present, if PS=0 continue, if PS=1 stop
 *
 * EXAMPLE: VA = 0x7FFE5E4ED123 (your process_a)
 *
 * STEP 1: CR3 → PML4[255]
 *   CR3 = 0x1337A3000
 *   PML4_phys = 0x1337A3000
 *   index = 255
 *   entry_phys = 0x1337A3000 + 255×8 = 0x1337A37F8
 *   entry = read(0x1337A37F8) = 0xXXXXXXXXXXXX
 *
 * STEP 2: PML4 entry → PDPT[511]
 *   PDPT_phys = entry & 0x000FFFFFFFFFF000
 *   index = 511
 *   entry = read(PDPT_phys + 511×8)
 *
 * STEP 3: PDPT entry → PD[295]
 *   PD_phys = entry & 0x000FFFFFFFFFF000
 *   index = 295
 *   entry = read(PD_phys + 295×8)
 *   if (entry & 0x80) → 2MB huge, stop here
 *
 * STEP 4: PD entry → PT[237]
 *   PT_phys = entry & 0x000FFFFFFFFFF000
 *   index = 237
 *   entry = read(PT_phys + 237×8)
 *
 * STEP 5: PT entry → final physical
 *   page_phys = entry & 0x000FFFFFFFFFF000
 *   offset = VA & 0xFFF = 0x123 = 291
 *   final_phys = page_phys | offset
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 07: Full 4KB Page Walk");

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL

static void walk_va(struct seq_file* m, unsigned long va) {
    unsigned long cr3, table_phys, entry;
    unsigned long pml4_idx, pdpt_idx, pd_idx, pt_idx, offset;
    int level;

    /* Read CR3 */
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    table_phys = cr3 & PTE_ADDR_MASK;

    /* Extract indices */
    pml4_idx = (va >> 39) & 0x1FF;
    pdpt_idx = (va >> 30) & 0x1FF;
    pd_idx = (va >> 21) & 0x1FF;
    pt_idx = (va >> 12) & 0x1FF;
    offset = va & 0xFFF;

    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "VA = 0x%lx\n", va);
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "Indices: PML4=%lu PDPT=%lu PD=%lu PT=%lu OFF=%lu\n\n", pml4_idx, pdpt_idx,
               pd_idx, pt_idx, offset);

    /* Level 4: PML4 */
    level = 4;
    entry = ((unsigned long*)__va(table_phys))[pml4_idx];
    seq_printf(m, "L4 PML4[%lu]: table=0x%lx entry=0x%016lx\n", pml4_idx, table_phys, entry);
    if (!(entry & 1)) {
        seq_printf(m, "  → NOT PRESENT\n");
        return;
    }
    table_phys = entry & PTE_ADDR_MASK;
    seq_printf(m, "  → next=0x%lx\n", table_phys);

    /* Level 3: PDPT */
    level = 3;
    entry = ((unsigned long*)__va(table_phys))[pdpt_idx];
    seq_printf(m, "L3 PDPT[%lu]: table=0x%lx entry=0x%016lx\n", pdpt_idx, table_phys, entry);
    if (!(entry & 1)) {
        seq_printf(m, "  → NOT PRESENT\n");
        return;
    }
    if ((entry >> 7) & 1) {
        unsigned long phys = (entry & 0x000FFFFFC0000000UL) | (va & 0x3FFFFFFF);
        seq_printf(m, "  → 1GB HUGE PAGE, phys=0x%lx\n", phys);
        return;
    }
    table_phys = entry & PTE_ADDR_MASK;
    seq_printf(m, "  → next=0x%lx\n", table_phys);

    /* Level 2: PD */
    level = 2;
    entry = ((unsigned long*)__va(table_phys))[pd_idx];
    seq_printf(m, "L2 PD[%lu]: table=0x%lx entry=0x%016lx\n", pd_idx, table_phys, entry);
    if (!(entry & 1)) {
        seq_printf(m, "  → NOT PRESENT\n");
        return;
    }
    if ((entry >> 7) & 1) {
        unsigned long phys = (entry & 0x000FFFFFFFE00000UL) | (va & 0x1FFFFF);
        seq_printf(m, "  → 2MB HUGE PAGE, phys=0x%lx\n", phys);
        return;
    }
    table_phys = entry & PTE_ADDR_MASK;
    seq_printf(m, "  → next=0x%lx\n", table_phys);

    /* Level 1: PT */
    level = 1;
    entry = ((unsigned long*)__va(table_phys))[pt_idx];
    seq_printf(m, "L1 PT[%lu]: table=0x%lx entry=0x%016lx\n", pt_idx, table_phys, entry);
    if (!(entry & 1)) {
        seq_printf(m, "  → NOT PRESENT\n");
        return;
    }

    unsigned long page_phys = entry & PTE_ADDR_MASK;
    unsigned long final_phys = page_phys | offset;
    seq_printf(m, "  → 4KB PAGE, base=0x%lx\n", page_phys);
    seq_printf(m, "  → FINAL: 0x%lx | 0x%lx = 0x%lx\n\n", page_phys, offset, final_phys);
}

static int demo_walk4kb_show(struct seq_file* m, void* v) {
    unsigned long test_vas[] = {
        0xFFFFFFFF81000000UL, /* kernel text */
        (unsigned long)m,     /* seq_file pointer (kernel heap) */
    };
    int i;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 07: 4KB PAGE WALK\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    for (i = 0; i < 2; i++) {
        walk_va(m, test_vas[i]);
    }

    return 0;
}

static int demo_walk4kb_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_walk4kb_show, NULL);
}

static const struct proc_ops demo_walk4kb_ops = {
    .proc_open = demo_walk4kb_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_walk4kb_init(void) {
    proc_create("demo_walk4kb", 0444, NULL, &demo_walk4kb_ops);
    pr_info("demo_walk4kb: loaded\n");
    return 0;
}

static void __exit demo_walk4kb_exit(void) { remove_proc_entry("demo_walk4kb", NULL); }

module_init(demo_walk4kb_init);
module_exit(demo_walk4kb_exit);
