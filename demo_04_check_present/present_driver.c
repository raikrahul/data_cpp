/*
 * DEMO 04: CHECK PRESENT BIT
 * ══════════════════════════
 *
 * ENTRY FORMAT: 64 bits
 * bit 0 = Present (P)
 *   1 = valid entry
 *   0 = not present → page fault if accessed
 *
 * EXAMPLE 1: entry = 0x80000002FAE001A1
 *   0x1A1 = 0001_1010_0001
 *   bit 0 = 1 → Present ✓
 *
 * EXAMPLE 2: entry = 0x0000000000000000
 *   bit 0 = 0 → Not Present ✗
 *
 * EXAMPLE 3: entry = 0x80000002FAE001A0
 *   0x1A0 = 0001_1010_0000
 *   bit 0 = 0 → Not Present ✗
 *   (has address bits but still not present!)
 *
 * OTHER FLAGS (for reference):
 *   bit 1 = R/W (0=read-only, 1=writable)
 *   bit 2 = U/S (0=kernel, 1=user)
 *   bit 5 = Accessed
 *   bit 6 = Dirty
 *   bit 7 = PS (Page Size)
 *   bit 63 = NX (No Execute)
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 04: Check Present Bit");

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL

static int is_present(unsigned long entry) {
    /* entry & 1 = extract bit 0 */
    return (entry & 1) ? 1 : 0;
}

static void decode_flags(struct seq_file* m, unsigned long entry) {
    seq_printf(m, "  bit 0 (P):   %lu → %s\n", entry & 1, (entry & 1) ? "Present" : "Not Present");
    seq_printf(m, "  bit 1 (RW):  %lu → %s\n", (entry >> 1) & 1,
               ((entry >> 1) & 1) ? "Writable" : "Read-only");
    seq_printf(m, "  bit 2 (US):  %lu → %s\n", (entry >> 2) & 1,
               ((entry >> 2) & 1) ? "User" : "Kernel");
    seq_printf(m, "  bit 5 (A):   %lu → %s\n", (entry >> 5) & 1,
               ((entry >> 5) & 1) ? "Accessed" : "Not accessed");
    seq_printf(m, "  bit 6 (D):   %lu → %s\n", (entry >> 6) & 1,
               ((entry >> 6) & 1) ? "Dirty" : "Clean");
    seq_printf(m, "  bit 7 (PS):  %lu → %s\n", (entry >> 7) & 1,
               ((entry >> 7) & 1) ? "Huge Page" : "Table");
    seq_printf(m, "  bit 63 (NX): %lu → %s\n", (entry >> 63) & 1,
               ((entry >> 63) & 1) ? "No Execute" : "Executable");
}

static int demo_present_show(struct seq_file* m, void* v) {
    unsigned long cr3, pml4_phys;
    unsigned long* pml4_virt;
    unsigned long entry;
    int i;
    int present_count = 0;

    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    pml4_phys = cr3 & PTE_ADDR_MASK;
    pml4_virt = (unsigned long*)__va(pml4_phys);

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 04: CHECK PRESENT BIT\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "FORMULA: is_present = entry & 1\n\n");

    /* Count present entries */
    for (i = 0; i < 512; i++) {
        if (pml4_virt[i] & 1) present_count++;
    }
    seq_printf(m, "PML4 entries present: %d / 512\n\n", present_count);

    /* Show user space entries */
    seq_printf(m, "USER SPACE (0-255):\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    for (i = 0; i < 256; i++) {
        entry = pml4_virt[i];
        if (entry & 1) {
            seq_printf(m, "PML4[%d] = 0x%016lx\n", i, entry);
            decode_flags(m, entry);
            seq_printf(m, "\n");
        }
    }

    /* Show first 5 kernel space entries */
    seq_printf(m, "KERNEL SPACE (256-511, first 5 present):\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");
    int shown = 0;
    for (i = 256; i < 512 && shown < 5; i++) {
        entry = pml4_virt[i];
        if (entry & 1) {
            seq_printf(m, "PML4[%d] = 0x%016lx\n", i, entry);
            decode_flags(m, entry);
            seq_printf(m, "\n");
            shown++;
        }
    }

    return 0;
}

static int demo_present_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_present_show, NULL);
}

static const struct proc_ops demo_present_ops = {
    .proc_open = demo_present_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_present_init(void) {
    proc_create("demo_present", 0444, NULL, &demo_present_ops);
    pr_info("demo_present: loaded\n");
    return 0;
}

static void __exit demo_present_exit(void) { remove_proc_entry("demo_present", NULL); }

module_init(demo_present_init);
module_exit(demo_present_exit);
