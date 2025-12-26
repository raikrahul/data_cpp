/*
 * DEMO 11: DUMP PML4 TABLE
 * ========================
 *
 * WHAT THIS DRIVER DOES:
 * Reads all 512 entries of the current PML4 table and displays them.
 * Shows which entries are present, which are kernel vs user space.
 *
 * PML4 TABLE STRUCTURE:
 *
 *   ┌────────────────────────────────────────────────────────────┐
 *   │ PML4 Table at physical CR3 address                        │
 *   ├───────────────────────────────────────────────────────────┬┤
 *   │ Index │ Entry (8 bytes)      │ Covers                     │
 *   ├───────┼──────────────────────┼────────────────────────────┤
 *   │ 0     │ 0x0000000000000000   │ 0x0000_0000_0000_0000      │
 *   │ 1     │ 0x0000000000000000   │ 0x0000_0080_0000_0000      │
 *   │ ...   │ ...                  │ ...                        │
 *   │ 255   │ 0x00000001234567067  │ 0x0000_7F80_0000_0000 (MAX USER) │
 *   │ 256   │ 0x0000000ABCDEF8067  │ 0xFFFF_8000_0000_0000 (KERNEL START) │
 *   │ ...   │ ...                  │ ...                        │
 *   │ 511   │ 0x00000002FB845067   │ 0xFFFF_FF80_0000_0000      │
 *   └───────┴──────────────────────┴────────────────────────────┘
 *
 * EACH PML4 ENTRY COVERS:
 *   512 GB of virtual address space
 *   = 512 × 1 GB (PDPT entries)
 *   = 512 × 512 × 2 MB (PD entries)
 *   = 512 × 512 × 512 × 4 KB (PT entries)
 *   = 2^39 bytes = 549,755,813,888 bytes
 *
 * CALCULATION:
 *   512 GB = 512 × 1,073,741,824 = 549,755,813,888 bytes ✓
 *
 * VIRTUAL ADDRESS RANGES:
 *   PML4[0]:   0x0000_0000_0000_0000 to 0x0000_007F_FFFF_FFFF (512 GB)
 *   PML4[1]:   0x0000_0080_0000_0000 to 0x0000_00FF_FFFF_FFFF (512 GB)
 *   ...
 *   PML4[255]: 0x0000_7F80_0000_0000 to 0x0000_7FFF_FFFF_FFFF (last user)
 *   PML4[256]: 0xFFFF_8000_0000_0000 to 0xFFFF_807F_FFFF_FFFF (first kernel)
 *   ...
 *   PML4[511]: 0xFFFF_FF80_0000_0000 to 0xFFFF_FFFF_FFFF_FFFF (last kernel)
 *
 * YOUR MACHINE OBSERVED:
 *   page_offset_base = 0xFFFF89DF00000000
 *   (0xFFFF89DF00000000 >> 39) & 0x1FF = 275
 *   → Direct map lives in PML4[273-276] region
 */

#include <asm/pgtable.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 11: Dump All PML4 Entries");

extern unsigned long page_offset_base;

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL

/*
 * Entry flags at bit positions:
 *   bit 0: P (Present)
 *   bit 1: RW (Read/Write)
 *   bit 2: US (User/Supervisor)
 *   bit 3: PWT (Page Write-Through)
 *   bit 4: PCD (Page Cache Disable)
 *   bit 5: A (Accessed)
 *   bit 7: PS (Page Size) - reserved in PML4
 *   bit 63: NX (No Execute)
 */
static void decode_flags(struct seq_file* m, unsigned long entry) {
    seq_printf(m, "%c%c%c%c%c%c", (entry & (1UL << 0)) ? 'P' : '-', /* Present */
               (entry & (1UL << 1)) ? 'W' : 'R',                    /* Write/Read-only */
               (entry & (1UL << 2)) ? 'U' : 'K',                    /* User/Kernel */
               (entry & (1UL << 5)) ? 'A' : '-',                    /* Accessed */
               (entry & (1UL << 6)) ? 'D' : '-',                    /* Dirty */
               (entry & (1UL << 63)) ? 'X' : '-');                  /* NX (No Execute) */
}

static int dump_pml4_show(struct seq_file* m, void* v) {
    unsigned long cr3, pml4_phys;
    unsigned long* pml4_virt;
    unsigned long entry, next_phys;
    int i;
    int present_count = 0;
    int user_present = 0;
    int kernel_present = 0;
    unsigned long va_start;

    /* Read CR3 */
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    pml4_phys = cr3 & PTE_ADDR_MASK;

    /* Convert to virtual for dereferencing */
    pml4_virt = (unsigned long*)__va(pml4_phys);

    seq_printf(m, "═══════════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 11: PML4 TABLE DUMP\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "CR3:             0x%016lx\n", cr3);
    seq_printf(m, "PML4 Physical:   0x%lx\n", pml4_phys);
    seq_printf(m, "PML4 Virtual:    0x%lx\n", (unsigned long)pml4_virt);
    seq_printf(m, "page_offset_base: 0x%lx\n", page_offset_base);
    seq_printf(m, "Direct map PML4 index: %lu\n\n", (page_offset_base >> 39) & 0x1FF);

    seq_printf(m, "USER SPACE (PML4[0:255]):\n");
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");

    /* Dump user space entries (0-255) */
    for (i = 0; i < 256; i++) {
        entry = pml4_virt[i];
        if (entry & 1) { /* Present */
            va_start = (unsigned long)i << 39;
            next_phys = entry & PTE_ADDR_MASK;

            seq_printf(m, "PML4[%3d] = 0x%016lx → PDPT @ 0x%lx  ", i, entry, next_phys);
            decode_flags(m, entry);
            seq_printf(m, "  VA: 0x%012lx\n", va_start);

            present_count++;
            user_present++;
        }
    }

    if (user_present == 0) {
        seq_printf(m, "  (All entries NOT PRESENT)\n");
    }

    seq_printf(m, "\nKERNEL SPACE (PML4[256:511]):\n");
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");

    /* Dump kernel space entries (256-511) */
    for (i = 256; i < 512; i++) {
        entry = pml4_virt[i];
        if (entry & 1) { /* Present */
            /* Calculate kernel VA (with sign extension) */
            va_start = 0xFFFF000000000000UL | ((unsigned long)i << 39);
            next_phys = entry & PTE_ADDR_MASK;

            seq_printf(m, "PML4[%3d] = 0x%016lx → PDPT @ 0x%lx  ", i, entry, next_phys);
            decode_flags(m, entry);
            seq_printf(m, "  VA: 0x%lx\n", va_start);

            present_count++;
            kernel_present++;
        }
    }

    seq_printf(m, "\nSUMMARY:\n");
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");
    seq_printf(m, "Total Present:   %d / 512\n", present_count);
    seq_printf(m, "User Present:    %d / 256 (entries 0-255)\n", user_present);
    seq_printf(m, "Kernel Present:  %d / 256 (entries 256-511)\n", kernel_present);
    seq_printf(m, "Not Present:     %d / 512\n", 512 - present_count);
    seq_printf(m, "\n");
    seq_printf(m, "Page Table Memory (PML4 only): 512 × 8 = 4096 bytes\n");
    seq_printf(m, "Each entry covers: 512 GB (2^39 bytes)\n");
    seq_printf(m, "Total addressable: 512 × 512 GB = 256 TB (2^48 bytes)\n");

    return 0;
}

static int dump_pml4_open(struct inode* inode, struct file* file) {
    return single_open(file, dump_pml4_show, NULL);
}

static const struct proc_ops dump_pml4_ops = {
    .proc_open = dump_pml4_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init dump_pml4_init(void) {
    proc_create("demo_pml4", 0444, NULL, &dump_pml4_ops);
    pr_info("demo_pml4: module loaded. Read /proc/demo_pml4\n");
    return 0;
}

static void __exit dump_pml4_exit(void) {
    remove_proc_entry("demo_pml4", NULL);
    pr_info("demo_pml4: module unloaded\n");
}

module_init(dump_pml4_init);
module_exit(dump_pml4_exit);
