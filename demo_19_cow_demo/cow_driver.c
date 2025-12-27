/*
 * DEMO 19: COPY-ON-WRITE
 * ══════════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input: Process A forks Process B.
 *    Action: Share Physical Pages. Mark Read-Only.
 *    Output: A and B see same data. Memory usage = 1x (not 2x).
 *
 *    Computation:
 *    Parent: Virt 0x4000 -> Phys 0x9000 (R=1, W=0).
 *    Child:  Virt 0x4000 -> Phys 0x9000 (R=1, W=0).
 *
 * 2. WHY:
 *    - Efficiency.
 *    - `fork()` is often followed by `exec()`.
 *    - If we copied 1GB of Parent RAM to Child, and Child immediately
 *      replaced it with `exec()`, we wasted 1GB copy time.
 *
 * 3. WHERE:
 *    - Page Table Entries (R/W bit = 0).
 *    - `vm_area_struct` (VM_WRITE = 1).
 *    - Mismatch (PTE=RO, VMA=RW) triggers Logic.
 *
 * 4. WHO:
 *    - Page Fault Handler.
 *    - Sees Write Fault on Read-Only page.
 *    - Checks VMA: "Is this SUPPOSED to be writable?"
 *    - Yes -> It's a COW page -> Copy it.
 *
 * 5. WHEN:
 *    - `fork()`.
 *    - `mmap()` private file mappings.
 *
 * 6. WITHOUT:
 *    - Fork bombing would be trivial (OOM instantly).
 *    - Chrome/Apache process creation would be 100x slower.
 *
 * 7. WHICH:
 *    - Anonymous private pages.
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: School Worksheet
 * - Teacher has 1 Master Copy.
 * - Class has 30 Students.
 *
 * Naive (No COW):
 * - Teacher photocopies 30 times. (Slow, Wastes Paper).
 * - Students read.
 *
 * COW:
 * - Teacher projects Master Copy on board. (0 Paper).
 * - Students read.
 * - Student A wants to write an answer.
 * - Student A copies text to their notebook (1 Page used).
 * - Writes on notebook.
 * - 29 Students still reading board.
 */

#include <linux/mm.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 19: Copy-on-Write");

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL

static int demo_cow_show(struct seq_file* m, void* v) {
    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 19: COPY-ON-WRITE (COW)\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "FORK WITHOUT COW:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  Parent: 100 MB of data\n");
    seq_printf(m, "  fork() → copy 100 MB to child (slow)\n");
    seq_printf(m, "  Total RAM: 200 MB\n");
    seq_printf(m, "  Time: O(memory size)\n\n");

    seq_printf(m, "FORK WITH COW:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  Parent: 100 MB of data\n");
    seq_printf(m, "  fork() → share pages, mark read-only\n");
    seq_printf(m, "  Total RAM: 100 MB (shared)\n");
    seq_printf(m, "  Time: O(page tables only)\n\n");

    seq_printf(m, "ON WRITE:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  1. Child writes to page\n");
    seq_printf(m, "  2. Page fault (write to read-only)\n");
    seq_printf(m, "  3. Kernel checks: COW page?\n");
    seq_printf(m, "  4. Allocate new physical page\n");
    seq_printf(m, "  5. Copy old page to new page\n");
    seq_printf(m, "  6. Update child's PTE: new phys, RW=1\n");
    seq_printf(m, "  7. Resume child at write instruction\n\n");

    seq_printf(m, "PTE FLAGS CHANGE:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  Before fork:  entry & 2 = 1 (RW)\n");
    seq_printf(m, "  After fork:   entry & 2 = 0 (RO) ← both processes\n");
    seq_printf(m, "  After write:  entry & 2 = 1 (RW) ← only writer\n\n");

    /* Show current process's page table write bits */
    seq_printf(m, "CURRENT PROCESS PAGE TABLE:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    unsigned long cr3;
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    unsigned long pml4_phys = cr3 & PTE_ADDR_MASK;
    unsigned long* pml4 = (unsigned long*)__va(pml4_phys);

    int ro_count = 0, rw_count = 0;
    int i;
    for (i = 0; i < 256; i++) {
        if (pml4[i] & 1) {
            if (pml4[i] & 2)
                rw_count++;
            else
                ro_count++;
        }
    }

    seq_printf(m, "  User space PML4 entries:\n");
    seq_printf(m, "  RW=1: %d entries\n", rw_count);
    seq_printf(m, "  RW=0: %d entries\n", ro_count);

    return 0;
}

static int demo_cow_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_cow_show, NULL);
}

static const struct proc_ops demo_cow_ops = {
    .proc_open = demo_cow_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_cow_init(void) {
    proc_create("demo_cow", 0444, NULL, &demo_cow_ops);
    pr_info("demo_cow: loaded\n");
    return 0;
}

static void __exit demo_cow_exit(void) { remove_proc_entry("demo_cow", NULL); }

module_init(demo_cow_init);
module_exit(demo_cow_exit);
