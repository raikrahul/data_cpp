/*
 * DEMO 03: READ PAGE TABLE ENTRY
 * ══════════════════════════════
 *
 * AXIOMATIC DIAGNOSIS (7 Ws)
 * ──────────────────────────
 *
 * 1. WHAT:
 *    Input 1: Table_Base_Phys = 0x1337A3000 (from CR3)
 *    Input 2: Index = 255 (extracted from VA 0x7FFE5E4ED123)
 *    Action:  Calculate exact byte address of entry #255
 *    Output:  Entry_Phys = 0x1337A37F8
 *
 *    Computation:
 *    Entry_Phys = Base + (Index × Entry_Size)
 *    Entry_Phys = 0x1337A3000 + (255 × 8)
 *    Entry_Phys = 0x1337A3000 + 2040 (decimal)
 *    Entry_Phys = 0x1337A3000 + 0x7F8 (hex)
 *      0x1337A3000
 *    +       0x7F8
 *    ─────────────
 *      0x1337A37F8 ✓
 *
 * 2. WHY:
 *    - Memory is byte-addressable.
 *    - Each PML4 entry is 64 bits = 8 bytes wide.
 *    - Entry #0 is at +0 bytes.
 *    - Entry #1 is at +8 bytes.
 *    - Entry #255 is at +2040 bytes.
 *    ∴ To read the 256th slot, we must offset by 255 × 8.
 *
 * 3. WHERE:
 *    - Physical Reality: Slot is at RAM address 0x1337A37F8
 *    - Kernel Reality:   CPU cannot load physical directly.
 *    - Virtual Mapping:  Must use Direct Map (page_offset_base).
 *    - Target: 0xFFFF89DF00000000 + 0x1337A37F8 = 0xFFFF89E0337A37F8
 *
 * 4. WHO:
 *    - HW: MMU shifter (Index*8) and adder (Base+Offset).
 *    - SW: `table_virt[index]` in C compiles to `MOV RAX, [Base + Index*8]`.
 *
 * 5. WHEN:
 *    - During page walk (Virtual → Physical translation).
 *    - This is Step 1: Locating the PDPT pointer.
 *
 * 6. WITHOUT:
 *    - If we just read 0x1337A37F8 (raw):
 *      - CPU interprets it as Virtual Address.
 *      - User space? Yes (< 0x7FFFFFFFFFFF).
 *      - Mapped? No.
 *      - Result: Page Fault (CR2 = 0x1337A37F8).
 *    - ∴ __va() is mandatory.
 *
 * 7. WHICH:
 *    - Which specific 8 bytes?
 *    - Bytes [0x1337A37F8] to [0x1337A37FF] inclusive.
 *    - 8 bytes total.
 *
 * ════════════════════════════════
 * DISTINCT NUMERICAL PUZZLE
 * ════════════════════════════════
 * Scenario: Warehouse 'RAM'
 * - Aisle 0 starts at meter 1,000,000.
 * - Each Box is 8 meters wide.
 * - We need Box 255.
 *
 * Calculation:
 * 1. Stride = 8 meters.
 * 2. Distance = 255 boxes × 8 meters/box = 2,040 meters.
 * 3. Location = 1,000,000 + 2,040 = 1,002,040 meters.
 *
 * Verification:
 * - Box 0: 1,000,000
 * - Box 1: 1,000,008
 * ...
 * - Box 255: 1,002,040 ✓
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
 * CALCULATION TRACE:
 * Input: table_phys = 0x1337A3000
 * Input: index = 255
 *
 * 1. Offset = 255 << 3 (multiply by 8)
 *    11111111 << 3 = 11111111000 = 0x7F8
 *
 * 2. Phys_Addr = 0x1337A3000 | 0x7F8
 *    (OR works because low 12 bits of table_phys are 0)
 *    = 0x1337A37F8
 *
 * 3. Virt_Addr = page_offset_base + Phys_Addr
 *    = 0xFFFF89DF00000000 + 0x1337A37F8
 *    = 0xFFFF89E0337A37F8
 *
 * 4. Load = *(unsigned long *)0xFFFF89E0337A37F8
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

    /*
     * MASKING AXIOM:
     * CR3 = 0x1337A3000
     * Mask = 0x000FFFFFFFFFF000
     * Result = 0x1337A3000 (Bits 63-52 cleared, Bits 11-0 cleared)
     */
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
