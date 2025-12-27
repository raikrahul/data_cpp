/*
 * DEMO 07: FULL 4KB PAGE WALK
 * ═══════════════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input: Virtual Address (VA) = 0x7FFE5E4ED123
 *    Process: 4-Level Descent (Tree Traversal)
 *    Output: Physical Address (PA) + Page Content
 *
 *    Trace AXIOMS:
 *    1. CR3 -> PML4 (Physical Base)
 *    2. PML4[Index4] -> PDPT Base
 *    3. PDPT[Index3] -> PD Base
 *    4. PD[Index2] -> PT Base
 *    5. PT[Index1] -> Page Base
 *    6. Page Base + Offset -> Final PA
 *
 * 2. WHY:
 *    - To translate sparse Virtual Space to dense Physical RAM.
 *    - To provide isolation (Process A cannot walk Process B's tree).
 *    - To allow paging to disk (Present bit).
 *
 * 3. WHERE:
 *    - Entirely in RAM. Accessing RAM to find where RAM is.
 *    - Each step requires a memory read (expensive).
 *    - Hence TLB (Demo 18) caches the result.
 *
 * 4. WHO:
 *    - MMU (Hardware Page Walker).
 *    - On "TLB Miss", MMU pauses CPU, walks tree, loads TLB, resumes.
 *
 * 5. WHEN:
 *    - Every memory access not in TLB.
 *    - Worst case latency = 4 DRAM reads (~100ns each) = 400ns penalty.
 *
 * 6. WITHOUT:
 *    - Flat memory model (Segments?)
 *    - Fragmentation.
 *    - No memory protection.
 *
 * 7. WHICH:
 *    - Which indices?
 *    - VA broken into chunks of 9 bits.
 *    - PML4 = bits[47:39]
 *    - PDPT = bits[38:30]
 *    - PD   = bits[29:21]
 *    - PT   = bits[20:12]
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: Interstellar Mail
 * - Address: "Galaxy 5, System 2, Planet 9, House 40"
 * - Digits: 5-2-9-40
 *
 * Routing:
 * 1. Go to Universe Hub (CR3). Look up Galaxy 5.
 *    -> Result: Coordinates of Galaxy 5 Main Post (PML4).
 * 2. Go to Galaxy 5 Post. Look up System 2.
 *    -> Result: Coordinates of System 2 Hub (PDPT).
 * 3. Go to System 2 Hub. Look up Planet 9.
 *    -> Result: Coordinates of Planet 9 Local Office (PD).
 * 4. Go to Planet 9. Look up House 40.
 *    -> Result: GPS Coordinates of House (PT).
 *
 * Delivery:
 * - Drop package at Exact GPS Location (Physical Address).
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
