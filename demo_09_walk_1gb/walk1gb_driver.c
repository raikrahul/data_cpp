/*
 * DEMO 09: 1GB HUGE PAGE WALK
 * ═══════════════════════════
 *
 * Walk stops at PDPT level when PS=1
 * Offset = 30 bits instead of 12
 *
 * YOUR MACHINE:
 *   CPU flag pdpe1gb = present → supports 1GB pages
 *   But HugePages_Total = 0 → none pre-allocated
 *   To create: echo 1 > /sys/kernel/mm/hugepages/hugepages-1048576kB/nr_hugepages
 *
 * This demo reports if 1GB pages are found (unlikely on default config)
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 09: 1GB Huge Page Walk");

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL
#define HUGE_1GB_MASK 0x000FFFFFC0000000UL

static int demo_walk1gb_show(struct seq_file* m, void* v) {
    unsigned long cr3, pml4_phys, pdpt_phys;
    unsigned long *pml4, *pdpt;
    unsigned long entry;
    int i, j, found = 0;

    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    pml4_phys = cr3 & PTE_ADDR_MASK;
    pml4 = (unsigned long*)__va(pml4_phys);

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 09: 1GB HUGE PAGE SEARCH\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "1GB page: PS=1 at PDPT level\n");
    seq_printf(m, "offset = 30 bits = 0x3FFFFFFF = 1,073,741,823 bytes\n\n");

    seq_printf(m, "SCANNING ALL PDPT ENTRIES FOR PS=1:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    /* Scan kernel space */
    for (i = 256; i < 512; i++) {
        if (!(pml4[i] & 1)) continue;

        pdpt_phys = pml4[i] & PTE_ADDR_MASK;
        pdpt = (unsigned long*)__va(pdpt_phys);

        for (j = 0; j < 512; j++) {
            entry = pdpt[j];
            if (!(entry & 1)) continue;

            if ((entry >> 7) & 1) {
                seq_printf(m, "FOUND 1GB @ PML4[%d] PDPT[%d]\n", i, j);
                seq_printf(m, "  entry = 0x%016lx\n", entry);
                seq_printf(m, "  PS = (entry >> 7) & 1 = 1\n");
                seq_printf(m, "  phys_base = entry & 0x%lx = 0x%lx\n", HUGE_1GB_MASK,
                           entry & HUGE_1GB_MASK);
                found++;
            }
        }
    }

    if (!found) {
        seq_printf(m, "No 1GB huge pages found.\n\n");
        seq_printf(m, "TO CREATE 1GB HUGE PAGES:\n");
        seq_printf(m, "  # Check if supported\n");
        seq_printf(m, "  cat /proc/cpuinfo | grep pdpe1gb\n");
        seq_printf(m, "  # Allocate 1GB hugepages\n");
        seq_printf(m, "  echo 1 > /sys/kernel/mm/hugepages/hugepages-1048576kB/nr_hugepages\n");
    } else {
        seq_printf(m, "\nTotal 1GB pages found: %d\n", found);
    }

    return 0;
}

static int demo_walk1gb_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_walk1gb_show, NULL);
}

static const struct proc_ops demo_walk1gb_ops = {
    .proc_open = demo_walk1gb_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_walk1gb_init(void) {
    proc_create("demo_walk1gb", 0444, NULL, &demo_walk1gb_ops);
    pr_info("demo_walk1gb: loaded\n");
    return 0;
}

static void __exit demo_walk1gb_exit(void) { remove_proc_entry("demo_walk1gb", NULL); }

module_init(demo_walk1gb_init);
module_exit(demo_walk1gb_exit);
