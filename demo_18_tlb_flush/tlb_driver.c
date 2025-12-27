/*
 * DEMO 18: TLB FLUSH
 * ══════════════════
 *
 * TLB = Translation Lookaside Buffer
 * Cache of recent VA → PA translations
 *
 * Without TLB: every memory access = 4 page table reads
 * With TLB: if hit, 0 page table reads
 *
 * TLB must be flushed when:
 *   1. CR3 changes (process switch) → automatic
 *   2. Page table entry modified → manual flush
 *   3. munmap / mprotect → kernel does this
 *
 * YOUR CPU: AMD Ryzen 5 4600H
 *   L1 DTLB: 64 entries, 4KB pages
 *   L1 ITLB: 64 entries, 4KB pages
 *   L2 TLB: 2048 entries, 4KB/2MB
 */

#include <asm/tlbflush.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 18: TLB Flush");

static int demo_tlb_show(struct seq_file* m, void* v) {
    unsigned long cr3_before, cr3_after;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 18: TLB (Translation Lookaside Buffer)\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "TLB PURPOSE:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  Without TLB: VA→PA needs 4 RAM reads (page walk)\n");
    seq_printf(m, "  With TLB:    VA→PA needs 0 RAM reads (if cached)\n");
    seq_printf(m, "  Speedup:     ~100x for cached translations\n\n");

    seq_printf(m, "YOUR CPU TLB (AMD Ryzen 5 4600H):\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  L1 Data TLB:  64 entries (4KB pages)\n");
    seq_printf(m, "  L1 Instr TLB: 64 entries (4KB pages)\n");
    seq_printf(m, "  L2 TLB:       2048 entries (4KB/2MB)\n");
    seq_printf(m, "  L1 miss + L2 hit: ~7 cycles\n");
    seq_printf(m, "  L2 miss: full page walk ~100+ cycles\n\n");

    /* Read CR3 */
    asm volatile("mov %%cr3, %0" : "=r"(cr3_before));

    /* Demonstrate TLB flush (write same CR3 back) */
    seq_printf(m, "TLB FLUSH DEMONSTRATION:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  CR3 before: 0x%lx\n", cr3_before);

    /* Writing CR3 flushes non-global TLB entries */
    asm volatile("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax");

    asm volatile("mov %%cr3, %0" : "=r"(cr3_after));
    seq_printf(m, "  CR3 after:  0x%lx\n", cr3_after);
    seq_printf(m, "  TLB flushed (non-global entries invalidated)\n\n");

    seq_printf(m, "WHEN TLB IS FLUSHED:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  Context switch:  automatic (CR3 changes)\n");
    seq_printf(m, "  munmap:          kernel calls flush_tlb_range()\n");
    seq_printf(m, "  mprotect:        kernel calls flush_tlb_range()\n");
    seq_printf(m, "  PTE modified:    explicit invlpg or CR3 reload\n\n");

    seq_printf(m, "GLOBAL vs NON-GLOBAL:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  PTE bit 8 = Global\n");
    seq_printf(m, "  Global entries: kept across CR3 reload (kernel)\n");
    seq_printf(m, "  Non-global: flushed on CR3 reload (user pages)\n");

    return 0;
}

static int demo_tlb_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_tlb_show, NULL);
}

static const struct proc_ops demo_tlb_ops = {
    .proc_open = demo_tlb_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_tlb_init(void) {
    proc_create("demo_tlb", 0444, NULL, &demo_tlb_ops);
    pr_info("demo_tlb: loaded\n");
    return 0;
}

static void __exit demo_tlb_exit(void) { remove_proc_entry("demo_tlb", NULL); }

module_init(demo_tlb_init);
module_exit(demo_tlb_exit);
