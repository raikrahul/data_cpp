/*
 * DEMO 05: CHECK HUGE PAGE BIT
 * ════════════════════════════
 *
 * bit 7 = PS (Page Size)
 *   0 = entry points to next table
 *   1 = entry IS the page (huge page)
 *
 * WHERE PS BIT IS CHECKED:
 *   PML4: bit 7 reserved (must be 0)
 *   PDPT: bit 7 = 1 → 1 GB huge page
 *   PD:   bit 7 = 1 → 2 MB huge page
 *   PT:   no PS bit (always 4 KB)
 *
 * EXAMPLE FROM YOUR MACHINE:
 *   PD[180] = 0x80000002FAE001A1
 *   0x1A1 = 0001_1010_0001
 *   bit 7 = (0x1A1 >> 7) & 1 = 1 → HUGE PAGE (2 MB)
 *
 * OFFSET CALCULATION CHANGES:
 *   4 KB page: offset = bits [11:0] = 12 bits = 0xFFF
 *   2 MB page: offset = bits [20:0] = 21 bits = 0x1FFFFF
 *   1 GB page: offset = bits [29:0] = 30 bits = 0x3FFFFFFF
 *
 * ADDRESS MASK CHANGES:
 *   4 KB: mask = 0x000FFFFFFFFFF000 (clear low 12)
 *   2 MB: mask = 0x000FFFFFFFE00000 (clear low 21)
 *   1 GB: mask = 0x000FFFFFC0000000 (clear low 30)
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 05: Check Huge Page Bit");

extern unsigned long page_offset_base;

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL
#define HUGE_2MB_MASK 0x000FFFFFFFE00000UL
#define HUGE_1GB_MASK 0x000FFFFFC0000000UL

static int demo_huge_show(struct seq_file* m, void* v) {
    unsigned long cr3, pml4_phys, pdpt_phys, pd_phys;
    unsigned long *pml4, *pdpt, *pd;
    unsigned long entry;
    int i, j, huge_count = 0;

    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    pml4_phys = cr3 & PTE_ADDR_MASK;
    pml4 = (unsigned long*)__va(pml4_phys);

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 05: HUGE PAGE DETECTION\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "FORMULA: is_huge = (entry >> 7) & 1\n\n");
    seq_printf(m, "page_offset_base = 0x%lx\n\n", page_offset_base);

    /* Walk kernel space looking for huge pages */
    seq_printf(m, "SCANNING KERNEL SPACE FOR HUGE PAGES:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    for (i = 256; i < 512 && huge_count < 10; i++) {
        if (!(pml4[i] & 1)) continue;

        pdpt_phys = pml4[i] & PTE_ADDR_MASK;
        pdpt = (unsigned long*)__va(pdpt_phys);

        for (j = 0; j < 512 && huge_count < 10; j++) {
            entry = pdpt[j];
            if (!(entry & 1)) continue;

            /* Check for 1 GB huge page at PDPT level */
            if ((entry >> 7) & 1) {
                seq_printf(m, "1 GB HUGE @ PML4[%d] PDPT[%d]\n", i, j);
                seq_printf(m, "  entry = 0x%016lx\n", entry);
                seq_printf(m, "  bit 7 = 1 → 1 GB page\n");
                seq_printf(m, "  phys base = 0x%lx\n\n", entry & HUGE_1GB_MASK);
                huge_count++;
                continue;
            }

            /* Descend to PD */
            pd_phys = entry & PTE_ADDR_MASK;
            pd = (unsigned long*)__va(pd_phys);

            /* Check first few PD entries for 2 MB huge */
            int k;
            for (k = 0; k < 512 && huge_count < 10; k++) {
                entry = pd[k];
                if (!(entry & 1)) continue;

                if ((entry >> 7) & 1) {
                    seq_printf(m, "2 MB HUGE @ PML4[%d] PDPT[%d] PD[%d]\n", i, j, k);
                    seq_printf(m, "  entry = 0x%016lx\n", entry);
                    seq_printf(m, "  bit 7 = (0x%lx >> 7) & 1 = 1\n", entry & 0xFFF);
                    seq_printf(m, "  phys base = 0x%lx\n\n", entry & HUGE_2MB_MASK);
                    huge_count++;
                    if (huge_count >= 10) break;
                }
            }
        }
    }

    seq_printf(m, "Found %d huge pages (showing max 10)\n", huge_count);

    return 0;
}

static int demo_huge_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_huge_show, NULL);
}

static const struct proc_ops demo_huge_ops = {
    .proc_open = demo_huge_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_huge_init(void) {
    proc_create("demo_huge", 0444, NULL, &demo_huge_ops);
    pr_info("demo_huge: loaded\n");
    return 0;
}

static void __exit demo_huge_exit(void) { remove_proc_entry("demo_huge", NULL); }

module_init(demo_huge_init);
module_exit(demo_huge_exit);
