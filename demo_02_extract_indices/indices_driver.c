/*
 * DEMO 02: EXTRACT PAGE TABLE INDICES
 * ====================================
 *
 * WHAT THIS DRIVER DOES:
 * Given a virtual address, extracts PML4/PDPT/PD/PT indices and offset.
 * Shows the bit manipulation step by step.
 *
 * VIRTUAL ADDRESS LAYOUT (48-bit addressing on your machine):
 *
 *   63        48 47     39 38     30 29     21 20     12 11         0
 *   ├──────────┼─────────┼─────────┼─────────┼─────────┼───────────┤
 *   │ SIGN EXT │  PML4   │  PDPT   │   PD    │   PT    │  OFFSET   │
 *   │ 16 bits  │  9 bits │  9 bits │  9 bits │  9 bits │  12 bits  │
 *   └──────────┴─────────┴─────────┴─────────┴─────────┴───────────┘
 *
 *   Total: 16 + 9 + 9 + 9 + 9 + 12 = 64 bits ✓
 *   Effective: 48 bits (bits [47:0] are meaningful)
 *
 * CANONICAL ADDRESS RULES:
 *   bits [63:48] must be all copies of bit 47 (sign extension)
 *
 *   User space:   bit 47 = 0 → bits [63:48] = 0x0000
 *                 Range: 0x0000_0000_0000_0000 to 0x0000_7FFF_FFFF_FFFF
 *
 *   Kernel space: bit 47 = 1 → bits [63:48] = 0xFFFF
 *                 Range: 0xFFFF_8000_0000_0000 to 0xFFFF_FFFF_FFFF_FFFF
 *
 *   Non-canonical (gap): causes #GP fault
 *                 0x0000_8000_0000_0000 to 0xFFFF_7FFF_FFFF_FFFF
 *
 * EXAMPLE WITH VA = 0x7FFE5E4ED123 (from your process_a):
 *
 *   Binary (48 bits):
 *   0111_1111_1111_1110_0101_1110_0100_1110_1101_0001_0010_0011
 *
 *   Split by boundaries:
 *   PML4[47:39]:  0_1111_1111 = 255
 *   PDPT[38:30]:  1_1111_1111 = 511
 *   PD[29:21]:    0_1111_0010 = 242
 *   PT[20:12]:    0_1110_1101 = 237
 *   OFFSET[11:0]: 0001_0010_0011 = 0x123 = 291
 *
 * EXTRACTION FORMULAS:
 *   PML4_INDEX  = (VA >> 39) & 0x1FF   # shift right 39, mask 9 bits
 *   PDPT_INDEX  = (VA >> 30) & 0x1FF   # shift right 30, mask 9 bits
 *   PD_INDEX    = (VA >> 21) & 0x1FF   # shift right 21, mask 9 bits
 *   PT_INDEX    = (VA >> 12) & 0x1FF   # shift right 12, mask 9 bits
 *   OFFSET      = VA & 0xFFF           # mask 12 bits
 *
 * WHY 0x1FF?
 *   0x1FF = 0b111111111 = 9 ones = 2^9 - 1 = 511
 *   Masks to extract exactly 9 bits (0-511 range)
 *
 * WHY 0xFFF?
 *   0xFFF = 0b111111111111 = 12 ones = 2^12 - 1 = 4095
 *   Masks to extract 12 bits (0-4095 range, within 4KB page)
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 02: Extract Page Table Indices from Virtual Address");

/* Test virtual addresses from your machine */
static unsigned long test_vaddrs[] = {
    0x7FFE5E4ED123UL,     /* process_a stack */
    0x7FFE37DAF000UL,     /* process_b stack */
    0xFFFF89DF00000000UL, /* page_offset_base (direct map start) */
    0xFFFFFFFF9695B668UL, /* page_offset_base symbol address */
    0x0000000000001000UL, /* low user address */
    0x0000000000000000UL, /* NULL pointer */
    0x00007FFFFFFFFFFFUL, /* max user address */
    0xFFFF800000000000UL, /* kernel start */
    0xFFFFFFFFFFFFFFFFUL, /* max kernel address */
};
static int num_test_vaddrs = sizeof(test_vaddrs) / sizeof(test_vaddrs[0]);

/*
 * extract_and_show:
 *
 * Extracts all indices from VA and prints with calculations.
 *
 * CALCULATION TRACE FOR VA = 0x7FFE5E4ED123:
 *
 *   STEP 1: PML4 index
 *   0x7FFE5E4ED123 >> 39 = ?
 *
 *   0x7FFE5E4ED123 = 140,734,598,676,771 (decimal)
 *   2^39 = 549,755,813,888
 *   140,734,598,676,771 / 549,755,813,888 = 255.999...
 *   floor(255.999) = 255
 *   255 & 0x1FF = 255 (already in range)
 *
 *   PML4_INDEX = 255 ✓
 *
 *   STEP 2: PDPT index
 *   0x7FFE5E4ED123 >> 30 = ?
 *
 *   2^30 = 1,073,741,824
 *   140,734,598,676,771 / 1,073,741,824 = 131,071.999...
 *   floor = 131,071
 *   131,071 & 0x1FF = 131,071 mod 512 = 511
 *
 *   PDPT_INDEX = 511 ✓
 *
 *   STEP 3: PD index
 *   0x7FFE5E4ED123 >> 21 = ?
 *
 *   2^21 = 2,097,152
 *   140,734,598,676,771 / 2,097,152 = 67,108,146.96...
 *   floor = 67,108,146
 *   67,108,146 & 0x1FF = 67,108,146 mod 512 = 242
 *
 *   PD_INDEX = 242 ✓
 *
 *   STEP 4: PT index
 *   0x7FFE5E4ED123 >> 12 = ?
 *
 *   2^12 = 4,096
 *   140,734,598,676,771 / 4,096 = 34,359,370,989
 *   34,359,370,989 & 0x1FF = 34,359,370,989 mod 512 = 237
 *
 *   PT_INDEX = 237 ✓
 *
 *   STEP 5: Offset
 *   0x7FFE5E4ED123 & 0xFFF = 0x123 = 291
 *
 *   OFFSET = 291 ✓
 */
static void extract_and_show(struct seq_file* m, unsigned long vaddr) {
    unsigned long pml4_idx, pdpt_idx, pd_idx, pt_idx, offset;
    unsigned long shifted;
    const char* addr_type;

    /*
     * EXTRACTION:
     *
     * Each extraction: shift right to move bits to position [8:0], then mask.
     *
     * vaddr = 0x7FFE5E4ED123
     *
     * (vaddr >> 39):
     *   Binary before: 0111_1111_1111_1110_0101_1110_0100_1110_1101_0001_0010_0011
     *   After >> 39:   0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_1111_1111
     *   Result: 0xFF = 255
     */
    pml4_idx = (vaddr >> 39) & 0x1FF;
    pdpt_idx = (vaddr >> 30) & 0x1FF;
    pd_idx = (vaddr >> 21) & 0x1FF;
    pt_idx = (vaddr >> 12) & 0x1FF;
    offset = vaddr & 0xFFF;

    /* Determine address type based on bit 47 */
    if ((vaddr >> 47) == 0)
        addr_type = "USER";
    else if ((vaddr >> 47) == 0x1FFFF)
        addr_type = "KERNEL";
    else
        addr_type = "NON-CANONICAL (INVALID)";

    seq_printf(m, "───────────────────────────────────────────────────────────────\n");
    seq_printf(m, "VA: 0x%016lx (%s)\n", vaddr, addr_type);
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");

    /* Show bit layout */
    seq_printf(m, "\nBIT LAYOUT:\n");
    seq_printf(m, "  [63:48] SIGN = 0x%04lx\n", (vaddr >> 48) & 0xFFFF);
    seq_printf(m, "  [47:39] PML4 = 0x%03lx = %3lu\n", pml4_idx, pml4_idx);
    seq_printf(m, "  [38:30] PDPT = 0x%03lx = %3lu\n", pdpt_idx, pdpt_idx);
    seq_printf(m, "  [29:21] PD   = 0x%03lx = %3lu\n", pd_idx, pd_idx);
    seq_printf(m, "  [20:12] PT   = 0x%03lx = %3lu\n", pt_idx, pt_idx);
    seq_printf(m, "  [11:0]  OFF  = 0x%03lx = %3lu\n", offset, offset);

    /* Show calculations */
    seq_printf(m, "\nCALCULATIONS:\n");

    shifted = vaddr >> 39;
    seq_printf(m, "  PML4: (0x%lx >> 39) & 0x1FF = 0x%lx & 0x1FF = %lu\n", vaddr, shifted,
               pml4_idx);

    shifted = vaddr >> 30;
    seq_printf(m, "  PDPT: (0x%lx >> 30) & 0x1FF = 0x%lx & 0x1FF = %lu\n", vaddr, shifted,
               pdpt_idx);

    shifted = vaddr >> 21;
    seq_printf(m, "  PD:   (0x%lx >> 21) & 0x1FF = 0x%lx & 0x1FF = %lu\n", vaddr, shifted, pd_idx);

    shifted = vaddr >> 12;
    seq_printf(m, "  PT:   (0x%lx >> 12) & 0x1FF = 0x%lx & 0x1FF = %lu\n", vaddr, shifted, pt_idx);

    seq_printf(m, "  OFF:  0x%lx & 0xFFF = %lu\n", vaddr, offset);

    /* Show entry addresses (would be used in walk) */
    seq_printf(m, "\nENTRY OFFSETS (from table base):\n");
    seq_printf(m, "  PML4[%lu] at byte offset %lu (0x%lx)\n", pml4_idx, pml4_idx * 8, pml4_idx * 8);
    seq_printf(m, "  PDPT[%lu] at byte offset %lu (0x%lx)\n", pdpt_idx, pdpt_idx * 8, pdpt_idx * 8);
    seq_printf(m, "  PD[%lu]   at byte offset %lu (0x%lx)\n", pd_idx, pd_idx * 8, pd_idx * 8);
    seq_printf(m, "  PT[%lu]   at byte offset %lu (0x%lx)\n", pt_idx, pt_idx * 8, pt_idx * 8);

    seq_printf(m, "\n");
}

static int demo_indices_show(struct seq_file* m, void* v) {
    int i;

    seq_printf(m, "═══════════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 02: EXTRACT PAGE TABLE INDICES\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "FORMULA:\n");
    seq_printf(m, "  PML4_IDX = (VA >> 39) & 0x1FF   (9 bits, positions 47:39)\n");
    seq_printf(m, "  PDPT_IDX = (VA >> 30) & 0x1FF   (9 bits, positions 38:30)\n");
    seq_printf(m, "  PD_IDX   = (VA >> 21) & 0x1FF   (9 bits, positions 29:21)\n");
    seq_printf(m, "  PT_IDX   = (VA >> 12) & 0x1FF   (9 bits, positions 20:12)\n");
    seq_printf(m, "  OFFSET   = VA & 0xFFF           (12 bits, positions 11:0)\n\n");

    for (i = 0; i < num_test_vaddrs; i++) {
        extract_and_show(m, test_vaddrs[i]);
    }

    return 0;
}

static int demo_indices_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_indices_show, NULL);
}

static const struct proc_ops demo_indices_ops = {
    .proc_open = demo_indices_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_indices_init(void) {
    proc_create("demo_indices", 0444, NULL, &demo_indices_ops);
    pr_info("demo_indices: module loaded. Read /proc/demo_indices\n");
    return 0;
}

static void __exit demo_indices_exit(void) {
    remove_proc_entry("demo_indices", NULL);
    pr_info("demo_indices: module unloaded\n");
}

module_init(demo_indices_init);
module_exit(demo_indices_exit);
