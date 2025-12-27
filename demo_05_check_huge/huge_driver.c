/*
 * DEMO 05: CHECK HUGE PAGE BIT
 * ════════════════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input: L2 (PD) Entry or L3 (PDPT) Entry
 *    Action: Check Bit 7 (PS - Page Size)
 *    Output: 0 = Table Pointer, 1 = Huge Page
 *
 *    Computation:
 *    Entry = 0x80000002FAE001A1
 *    Bit 7 = (Entry >> 7) & 1
 *    0x1A1 in binary: ...0001_1010_0001
 *    Right Shift 7:   ...0000_0000_0011 (0x3)
 *    Limit to LSBit:  0x3 & 1 = 1
 *    ∴ Bit 7 is 1.
 *
 * 2. WHY:
 *    - To map 2MB or 1GB with fewer tables.
 *    - Standard 4KB: PML4 → PDPT → PD → PT → Page (4 levels)
 *    - Huge 2MB:     PML4 → PDPT → PD → Page (3 levels)
 *    - Huge 1GB:     PML4 → PDPT → Page (2 levels)
 *    - Saves RAM (fewer PTs). Saves TLB entries (coverage).
 *
 * 3. WHERE:
 *    - Bit 7 of the Entry.
 *    - ONLY valid at PDPT (L3) and PD (L2) levels.
 *    - Ignored/Reserved at PML4 (L4) and PT (L1).
 *
 * 4. WHO:
 *    - MMU (Hardware).
 *    - If Bit 7=1 at PD level:
 *      MMU stops walking. Uses Entry[51:21] as Base Address.
 *      Uses VA[20:0] as Offset.
 *
 * 5. WHEN:
 *    - During page walk.
 *    - At Step 2 (PDPT) or Step 3 (PD).
 *
 * 6. WITHOUT:
 *    - Must use 4KB pages for everything.
 *    - 1TB RAM would need 2GB just for Page Tables.
 *    - TLB thrashing on large datasets (DBs, VMs).
 *
 * 7. WHICH:
 *    - 2MB Page: PS=1 in PD. Offset = 21 bits (2MB).
 *    - 1GB Page: PS=1 in PDPT. Offset = 30 bits (1GB).
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: City Zoning
 * - Standard Zone: 4km x 4km blocks.
 * - Industrial Zone: 1 huge 100km x 100km block.
 *
 * Map Legend (bit 7):
 * - 0 = "See detailed sub-map for this sector"
 * - 1 = "This entire sector is one factory"
 *
 * Numerical Analogy:
 * - Address = 12345
 * - If Map[1] says "Standard":
 *   - Look up Map[12][3][4][5]
 * - If Map[1] says "Huge":
 *   - You are at Factory #1.
 *   - Location = Factory_Base + 2345 (Offset includes more digits).
 *
 * Contrast:
 * - 4KB Offset: 12 bits (0-4095)
 * - 2MB Offset: 21 bits (0-2097151)
 * - ∴ Huge page absorbs the next table's index into the offset.
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
        /* Check Present */
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
