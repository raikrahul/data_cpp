/*
 * DEMO 17: BUDDY ALLOCATOR
 * ═════════════════════════
 *
 * Buddy = physical page allocator
 *
 * Allocates 2^order contiguous pages
 * order 0 = 1 page = 4 KB
 * order 1 = 2 pages = 8 KB
 * ...
 * order 10 = 1024 pages = 4 MB (typical max)
 *
 * Splitting: if need 1 page but only 2-page block free,
 *            split into two 1-page buddies
 *
 * Coalescing: when free, check if buddy also free,
 *             merge into larger block
 */

#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 17: Buddy Allocator");

static int demo_buddy_show(struct seq_file* m, void* v) {
    struct page* pages[5];
    int orders[] = {0, 1, 2, 3, 4};
    int i;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 17: BUDDY ALLOCATOR\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "ORDER TABLE:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "  order 0 = 2^0 = 1 page = 4 KB\n");
    seq_printf(m, "  order 1 = 2^1 = 2 pages = 8 KB\n");
    seq_printf(m, "  order 2 = 2^2 = 4 pages = 16 KB\n");
    seq_printf(m, "  order 3 = 2^3 = 8 pages = 32 KB\n");
    seq_printf(m, "  order 4 = 2^4 = 16 pages = 64 KB\n");
    seq_printf(m, "  order 10 = 2^10 = 1024 pages = 4 MB\n\n");

    seq_printf(m, "ALLOCATIONS:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    for (i = 0; i < 5; i++) {
        pages[i] = alloc_pages(GFP_KERNEL, orders[i]);
        if (pages[i]) {
            unsigned long pfn = page_to_pfn(pages[i]);
            unsigned long phys = pfn << PAGE_SHIFT;
            unsigned long size = (1 << orders[i]) * PAGE_SIZE;

            seq_printf(m, "order %d: %d pages = %lu bytes\n", orders[i], 1 << orders[i], size);
            seq_printf(m, "  PFN = %lu, phys = 0x%lx\n\n", pfn, phys);
        } else {
            seq_printf(m, "order %d: FAILED\n\n", orders[i]);
        }
    }

    /* Free all */
    for (i = 0; i < 5; i++) {
        if (pages[i]) __free_pages(pages[i], orders[i]);
    }

    seq_printf(m, "All pages freed (merged back into buddy system)\n\n");

    seq_printf(m, "SEE: cat /proc/buddyinfo\n");

    return 0;
}

static int demo_buddy_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_buddy_show, NULL);
}

static const struct proc_ops demo_buddy_ops = {
    .proc_open = demo_buddy_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_buddy_init(void) {
    proc_create("demo_buddy", 0444, NULL, &demo_buddy_ops);
    pr_info("demo_buddy: loaded\n");
    return 0;
}

static void __exit demo_buddy_exit(void) { remove_proc_entry("demo_buddy", NULL); }

module_init(demo_buddy_init);
module_exit(demo_buddy_exit);
