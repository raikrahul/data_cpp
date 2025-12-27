/*
 * DEMO 06: EXTRACT PHYSICAL ADDRESS FROM ENTRY
 * ═════════════════════════════════════════════
 *
 * ENTRY: 0x80000002FAE001A1
 *
 * CASE 1: Points to table (PS=0)
 *   mask = 0x000FFFFFFFFFF000 (bits [51:12])
 *   0x80000002FAE001A1 & 0x000FFFFFFFFFF000 = 0x2FAE00000
 *   Next table at physical 0x2FAE00000
 *
 * CASE 2: 2 MB huge page (PS=1 at PD level)
 *   mask = 0x000FFFFFFFE00000 (bits [51:21])
 *   0x80000002FAE001A1 & 0x000FFFFFFFE00000 = 0x2FAE00000
 *   Page base at physical 0x2FAE00000
 *
 * CASE 3: 1 GB huge page (PS=1 at PDPT level)
 *   mask = 0x000FFFFFC0000000 (bits [51:30])
 *   0x80000002FAE001A1 & 0x000FFFFFC0000000 = 0x2C0000000
 *   Page base at physical 0x2C0000000
 *
 * MASK DERIVATION:
 *   4 KB: clear low 12 bits → mask = ~0xFFF & 0x000FFFFFFFFFFFFF
 *   2 MB: clear low 21 bits → mask = ~0x1FFFFF & 0x000FFFFFFFFFFFFF
 *   1 GB: clear low 30 bits → mask = ~0x3FFFFFFF & 0x000FFFFFFFFFFFFF
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 06: Extract Physical Address");

#define MASK_4KB 0x000FFFFFFFFFF000UL
#define MASK_2MB 0x000FFFFFFFE00000UL
#define MASK_1GB 0x000FFFFFC0000000UL

static int demo_addr_show(struct seq_file* m, void* v) {
    unsigned long test_entry = 0x80000002FAE001A1UL;
    unsigned long addr_4kb, addr_2mb, addr_1gb;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 06: EXTRACT PHYSICAL ADDRESS\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "TEST ENTRY: 0x%016lx\n\n", test_entry);

    /* 4 KB mask */
    addr_4kb = test_entry & MASK_4KB;
    seq_printf(m, "4 KB PAGE (table pointer):\n");
    seq_printf(m, "  mask = 0x%016lx (bits [51:12])\n", MASK_4KB);
    seq_printf(m, "  0x%lx & 0x%lx = 0x%lx\n\n", test_entry, MASK_4KB, addr_4kb);

    /* 2 MB mask */
    addr_2mb = test_entry & MASK_2MB;
    seq_printf(m, "2 MB HUGE PAGE:\n");
    seq_printf(m, "  mask = 0x%016lx (bits [51:21])\n", MASK_2MB);
    seq_printf(m, "  0x%lx & 0x%lx = 0x%lx\n\n", test_entry, MASK_2MB, addr_2mb);

    /* 1 GB mask */
    addr_1gb = test_entry & MASK_1GB;
    seq_printf(m, "1 GB HUGE PAGE:\n");
    seq_printf(m, "  mask = 0x%016lx (bits [51:30])\n", MASK_1GB);
    seq_printf(m, "  0x%lx & 0x%lx = 0x%lx\n\n", test_entry, MASK_1GB, addr_1gb);

    /* Show mask derivations */
    seq_printf(m, "MASK DERIVATIONS:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "4 KB: 2^12 - 1 = 4095 = 0xFFF → clear → bits [51:12]\n");
    seq_printf(m, "2 MB: 2^21 - 1 = 2097151 = 0x1FFFFF → clear → bits [51:21]\n");
    seq_printf(m, "1 GB: 2^30 - 1 = 1073741823 = 0x3FFFFFFF → clear → bits [51:30]\n");

    return 0;
}

static int demo_addr_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_addr_show, NULL);
}

static const struct proc_ops demo_addr_ops = {
    .proc_open = demo_addr_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_addr_init(void) {
    proc_create("demo_addr", 0444, NULL, &demo_addr_ops);
    pr_info("demo_addr: loaded\n");
    return 0;
}

static void __exit demo_addr_exit(void) { remove_proc_entry("demo_addr", NULL); }

module_init(demo_addr_init);
module_exit(demo_addr_exit);
