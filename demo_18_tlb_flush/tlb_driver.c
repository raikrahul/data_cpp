/*
 * DEMO 18: TLB FLUSH
 * ══════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input: Current Page Tables.
 *    Action: Invalidate CPU Cache of Translations.
 *    Output: Empty TLB (Misses guaranteed next time).
 *
 *    Computation:
 *    Write CR3 (Reload) -> Flushes all Non-Global entries.
 *    `invlpg` -> Flushes 1 specific entry.
 *
 * 2. WHY:
 *    - Coherency.
 *    - OS changes a Page Table Entry (e.g., marks page Read-Only).
 *    - CPU doesn't know. CPU still has "Read-Write" cached in TLB.
 *    - User writes to page -> Security Violation!
 *    - Solution: Flush TLB to force CPU to re-read PTE.
 *
 * 3. WHERE:
 *    - L1 TLB (Instructions/Data) inside Core.
 *    - L2 TLB (Shared) inside Core.
 *
 * 4. WHO:
 *    - Kernel Memory Management (mprotect, munmap).
 *    - Context Switcher.
 *
 * 5. WHEN:
 *    - Changing mappings.
 *    - Freeing memory.
 *    - Switching processes (Automatic CR3 write).
 *
 * 6. WITHOUT:
 *    - Stale Translations.
 *    - Use-After-Free vulnerabilities (Accessing freed RAM).
 *    - Correctness failure (COW doesn't trigger).
 *
 * 7. WHICH:
 *    - Global Pages (Kernel) are preserved (Bit 8 in PTE).
 *    - User Pages are flushed.
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: Pizza Delivery Speed Dial
 * - You order Pizza every Friday.
 * - You save "Pizza Place" in Speed Dial (TLB).
 * - Number: 555-0100.
 *
 * Event:
 * - Pizza Place moves. New Number: 555-0200.
 * - They update the Phone Book (Page Table).
 *
 * Failure:
 * - You hit Speed Dial. Call 555-0100.
 * - "Number Disconnected".
 *
 * Solution (Flush):
 * - Delete Speed Dial entry.
 * - Look up in Phone Book again.
 * - Save 555-0200.
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
