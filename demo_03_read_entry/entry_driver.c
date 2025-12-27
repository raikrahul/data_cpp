/*
 * DEMO 03: READ PAGE TABLE ENTRY
 * ══════════════════════════════
 *
 * DATA: table_phys = 0x1337A3000 (from CR3)
 * DATA: index = 255 (PML4 index for 0x7FFE5E4ED123)
 *
 * FORMULA: entry_address = table_phys + (index × 8)
 *
 * CALCULATION:
 *   entry_address = 0x1337A3000 + (255 × 8)
 *                 = 0x1337A3000 + 2040
 *                 = 0x1337A3000 + 0x7F8
 *                 = 0x1337A37F8
 *
 * TO READ: Need virtual address
 *   page_offset_base = 0xFFFF89DF00000000
 *   entry_virt = 0xFFFF89DF00000000 + 0x1337A37F8
 *              = 0xFFFF89E0337A37F8
 *
 * READ: *(unsigned long *)0xFFFF89E0337A37F8 = entry value
 *
 * ENTRY FORMAT (64 bits):
 *   bits [51:12] = physical address of next table
 *   bits [11:0]  = flags
 *   bit 63       = NX (No Execute)
 *
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 03: Read Page Table Entry");

extern unsigned long page_offset_base;

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL

/*
 * read_entry: Read 8 bytes from physical table address at index
 *
 * table_phys = 0x1337A3000
 * index = 255
 * → byte_offset = 255 × 8 = 2040 = 0x7F8
 * → entry_phys = 0x1337A3000 + 0x7F8 = 0x1337A37F8
 * → entry_virt = __va(0x1337A37F8) = 0xFFFF89E0337A37F8
 * → entry_value = *(0xFFFF89E0337A37F8)
 */
static unsigned long read_entry(unsigned long table_phys, unsigned long index) {
    unsigned long* table_virt;

    /* __va(phys) = page_offset_base + phys */
    table_virt = (unsigned long*)__va(table_phys);

    /* table_virt[index] = *(table_virt + index) = *(table_virt + index×8 bytes) */
    return table_virt[index];
}

static int demo_entry_show(struct seq_file* m, void* v) {
    unsigned long cr3, pml4_phys, entry;
    unsigned long byte_offset, entry_phys, entry_virt;
    int i;

    /* Read CR3 */
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    pml4_phys = cr3 & PTE_ADDR_MASK;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 03: READ PAGE TABLE ENTRY\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "CR3 = 0x%lx → PML4_phys = 0x%lx\n\n", cr3, pml4_phys);

    /* Read a few PML4 entries */
    seq_printf(m, "SAMPLE PML4 ENTRIES:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    for (i = 0; i < 5; i++) {
        byte_offset = i * 8;
        entry_phys = pml4_phys + byte_offset;
        entry_virt = (unsigned long)__va(entry_phys);
        entry = read_entry(pml4_phys, i);

        seq_printf(m, "PML4[%d]:\n", i);
        seq_printf(m, "  offset = %d × 8 = %lu bytes\n", i, byte_offset);
        seq_printf(m, "  phys = 0x%lx + 0x%lx = 0x%lx\n", pml4_phys, byte_offset, entry_phys);
        seq_printf(m, "  virt = 0x%lx\n", entry_virt);
        seq_printf(m, "  value = 0x%016lx\n", entry);
        seq_printf(m, "  present = %lu\n\n", entry & 1);
    }

    /* Kernel entries (256-260) */
    seq_printf(m, "KERNEL SPACE ENTRIES:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    for (i = 256; i < 261; i++) {
        entry = read_entry(pml4_phys, i);
        if (entry & 1) {
            seq_printf(m, "PML4[%d] = 0x%016lx → next = 0x%lx\n", i, entry, entry & PTE_ADDR_MASK);
        }
    }

    return 0;
}

static int demo_entry_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_entry_show, NULL);
}

static const struct proc_ops demo_entry_ops = {
    .proc_open = demo_entry_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_entry_init(void) {
    proc_create("demo_entry", 0444, NULL, &demo_entry_ops);
    pr_info("demo_entry: loaded\n");
    return 0;
}

static void __exit demo_entry_exit(void) { remove_proc_entry("demo_entry", NULL); }

module_init(demo_entry_init);
module_exit(demo_entry_exit);
