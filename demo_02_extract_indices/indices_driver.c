/*
 * DEMO 02: EXTRACT PAGE TABLE INDICES
 * ════════════════════════════════════
 *
 * DATA SOURCE: /proc/cpuinfo → "48 bits virtual"
 * ∴ VA = 48 bits = [47:0]
 *
 * DATA SOURCE: Intel SDM 4.5 → 4-level paging splits VA into 5 fields
 * ∴ 48 = 9 + 9 + 9 + 9 + 12
 *
 * [47:39] = 9 bits → PML4 index → 2^9 = 512 entries
 * [38:30] = 9 bits → PDPT index → 2^9 = 512 entries
 * [29:21] = 9 bits → PD index → 2^9 = 512 entries
 * [20:12] = 9 bits → PT index → 2^9 = 512 entries
 * [11:0] = 12 bits → offset → 2^12 = 4096 bytes
 *
 * ═══════════════════════════════════════════════════════════════════
 * EXAMPLE 1: VA = 0x7FFE5E4ED123 (from your process_a /proc/PID/maps)
 * ═══════════════════════════════════════════════════════════════════
 *
 * STEP 1: Convert to decimal
 * 0x7FFE5E4ED123 = 140,734,598,676,771
 *
 * STEP 2: Extract PML4 index [47:39]
 * 140,734,598,676,771 >> 39 = 140,734,598,676,771 / 549,755,813,888
 * = 255.9996...
 * floor(255.9996) = 255
 * 255 & 0x1FF = 255 (already < 512)
 * ∴ PML4 = 255
 *
 * STEP 3: Extract PDPT index [38:30]
 * 140,734,598,676,771 >> 30 = 140,734,598,676,771 / 1,073,741,824
 * = 131,071.999...
 * floor = 131,071
 * 131,071 & 0x1FF = 131,071 mod 512 = ?
 *   131,071 / 512 = 255.998
 *   255 × 512 = 130,560
 *   131,071 - 130,560 = 511
 * ∴ PDPT = 511
 *
 * STEP 4: Extract PD index [29:21]
 * 140,734,598,676,771 >> 21 = 140,734,598,676,771 / 2,097,152
 * = 67,108,146.96...
 * floor = 67,108,146
 * 67,108,146 & 0x1FF = 67,108,146 mod 512 = ?
 *   67,108,146 / 512 = 131,070.59
 *   131,070 × 512 = 67,107,840
 *   67,108,146 - 67,107,840 = 306
 * WAIT: Let me verify with hex
 * 0x7FFE5E4ED123 >> 21 = 0x3FFFAF27
 * 0x3FFFAF27 & 0x1FF = 0x127 = 295? No...
 *
 * CORRECT METHOD - use hex directly:
 * 0x7FFE5E4ED123 in bits:
 * 0111_1111_1111_1110_0101_1110_0100_1110_1101_0001_0010_0011
 * pos: 47...39  38...30  29...21  20...12  11...0
 *
 * bits[47:39] = 0_1111_1111 = 0xFF = 255 ✓
 * bits[38:30] = 1_1111_1111 = 0x1FF = 511 ✓
 * bits[29:21] = 0_1011_1100 = 0xBC = 188? Let me recount...
 *
 * Position map (right to left, 0-indexed):
 * bit 0 = rightmost = 1
 * 0x7FFE5E4ED123:
 *   0x123 = bits [11:0] = offset = 0x123 = 291
 *   0xED = bits [19:12]... no wait
 *
 * Let me use shift method:
 * (0x7FFE5E4ED123 >> 39) & 0x1FF:
 *   0x7FFE5E4ED123 >> 39 = 0xFF
 *   0xFF & 0x1FF = 0xFF = 255 ✓
 *
 * (0x7FFE5E4ED123 >> 30) & 0x1FF:
 *   0x7FFE5E4ED123 >> 30 = 0x1FFFF
 *   0x1FFFF & 0x1FF = 0x1FF = 511 ✓
 *
 * (0x7FFE5E4ED123 >> 21) & 0x1FF:
 *   0x7FFE5E4ED123 >> 21 = 0x3FFFAF27
 *   0x3FFFAF27 & 0x1FF = 0x127 = 295? No: 0x127 = 1_0010_0111 = 295
 *   Wait: 0x3FFFAF27 in binary low 9 bits:
 *   0x27 = 0010_0111
 *   Need bit 8 from 0xAF: 0xAF = 1010_1111, bit 0 of next nibble = 1
 *   So bits[8:0] of 0x3FFFAF27 = 1_0010_0111 = 0x127 = 295
 *   Hmm, that's different from my earlier 242.
 *
 * Let me verify in Python mentally:
 *   hex(0x7FFE5E4ED123 >> 21) = 0x3fffaf27
 *   hex(0x3fffaf27 & 0x1ff) = 0x127 = 295
 *
 * Earlier I said 242. WHICH IS WRONG?
 * 0x1FF = 511, 0x127 = 295. Let me recalculate:
 *   0x27 = 39, 0x100 = 256, 0x127 = 295 ✓
 *
 * So PD index = 295, not 242. Earlier calculation was wrong.
 *
 * (0x7FFE5E4ED123 >> 12) & 0x1FF:
 *   0x7FFE5E4ED123 >> 12 = 0x7FFE5E4ED
 *   0x7FFE5E4ED & 0x1FF = 0xED = 237 ✓
 *
 * 0x7FFE5E4ED123 & 0xFFF = 0x123 = 291 ✓
 *
 * ═══════════════════════════════════════════════════════════════════
 * CORRECTED RESULT FOR VA = 0x7FFE5E4ED123:
 * ═══════════════════════════════════════════════════════════════════
 * PML4 = (0x7FFE5E4ED123 >> 39) & 0x1FF = 255
 * PDPT = (0x7FFE5E4ED123 >> 30) & 0x1FF = 511
 * PD   = (0x7FFE5E4ED123 >> 21) & 0x1FF = 295
 * PT   = (0x7FFE5E4ED123 >> 12) & 0x1FF = 237
 * OFF  = 0x7FFE5E4ED123 & 0xFFF = 291
 *
 * ═══════════════════════════════════════════════════════════════════
 * EXAMPLE 2: VA = 0xFFFF89DF00000000 (page_offset_base from your machine)
 * ═══════════════════════════════════════════════════════════════════
 *
 * (0xFFFF89DF00000000 >> 39) & 0x1FF:
 *   0xFFFF89DF00000000 >> 39 = 0x1FFFF13BE
 *   0x1FFFF13BE & 0x1FF = 0x1BE = 446? No...
 *   0x3BE & 0x1FF = 0x1BE = 446? Let me check:
 *   0x1FFFF13BE low 9 bits: 0x13BE & 0x1FF = 0x1BE = 446
 *   Hmm, but kernel direct map should be around PML4[273-276]
 *
 * Let me recalculate:
 *   0xFFFF89DF00000000 >> 39 = 0xFFFF89DF00000000 / 2^39
 *   This is a SIGNED shift in C for negative numbers...
 *   As unsigned: 0xFFFF89DF00000000 = 18,446,502,271,276,015,616
 *   18,446,502,271,276,015,616 >> 39 = 33,552,859
 *   33,552,859 & 0x1FF = 33,552,859 mod 512 = ?
 *   33,552,859 / 512 = 65,533.7
 *   65,533 × 512 = 33,552,896
 *   33,552,859 - 33,552,896 = -37 → WRONG
 *
 * Let me try: 65,532 × 512 = 33,552,384
 * 33,552,859 - 33,552,384 = 475
 * Hmm, still not 273-276.
 *
 * Actually for kernel addresses (bit 47 = 1):
 * PML4 index = bits [47:39]
 * For 0xFFFF89DF00000000:
 *   bits [47:39] starting from bit 39
 *   0xFF...89DF... → need to look at bits 47-39
 *
 * 0xFFFF89DF00000000 in binary (64 bits):
 * 1111_1111_1111_1111_1000_1001_1101_1111_0000_0000_0000_0000_0000_0000_0000_0000
 *
 * bits [47:39]:
 *   bit 47 = 1, bit 46 = 0, bit 45 = 0, bit 44 = 0
 *   bit 43 = 1, bit 42 = 0, bit 41 = 0, bit 40 = 1
 *   bit 39 = 1
 *   = 1_0001_0011 = 0x113 = 275 ✓
 *
 * ∴ PML4 index for page_offset_base = 275
 *
 * ═══════════════════════════════════════════════════════════════════
 * MASK DERIVATION: WHY 0x1FF?
 * ═══════════════════════════════════════════════════════════════════
 *
 * Need 9-bit mask.
 * 9 bits, all ones = 2^9 - 1 = 512 - 1 = 511 = 0x1FF
 *
 * 0x1FF = 0001_1111_1111 = 9 ones ✓
 *
 * Alternative:
 *   9 / 4 = 2 remainder 1
 *   2 Fs + prefix for 1 bit = 1 + FF = 0x1FF ✓
 *
 * ═══════════════════════════════════════════════════════════════════
 * SHIFT VALUES DERIVATION
 * ═══════════════════════════════════════════════════════════════════
 *
 * VA layout: [47:39][38:30][29:21][20:12][11:0]
 *
 * To extract [47:39]: shift right by 39, mask 9 bits
 *   Why 39? [47:39] starts at bit 39. Shift moves bit 39 to bit 0.
 *
 * To extract [38:30]: shift right by 30, mask 9 bits
 *   Why 30? [38:30] starts at bit 30.
 *
 * To extract [29:21]: shift right by 21, mask 9 bits
 * To extract [20:12]: shift right by 12, mask 9 bits
 * To extract [11:0]: no shift, mask 12 bits (0xFFF)
 *
 * Shift values: 39, 30, 21, 12, 0
 * Pattern: 39-9=30, 30-9=21, 21-9=12, 12-12=0 ✓
 *
 */

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 02: Extract Page Table Indices");

/* Test VAs from your machine */
static unsigned long test_vaddrs[] = {
    0x7FFE5E4ED123UL,     /* your process_a stack */
    0xFFFF89DF00000000UL, /* your page_offset_base */
    0x0000000000001000UL, /* minimal user VA */
    0xFFFFFFFFFFFFFFFFUL, /* max kernel VA */
};
#define NUM_VADDRS (sizeof(test_vaddrs) / sizeof(test_vaddrs[0]))

/*
 * Extract and display indices with full calculation trace
 */
static void show_extraction(struct seq_file* m, unsigned long va) {
    unsigned long pml4, pdpt, pd, pt, off;
    unsigned long shifted;

    seq_printf(m, "────────────────────────────────────────────────────────\n");
    seq_printf(m, "VA = 0x%016lx\n", va);
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    /* PML4: bits [47:39] */
    shifted = va >> 39;
    pml4 = shifted & 0x1FF;
    seq_printf(m, "PML4: 0x%lx >> 39 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pml4);

    /* PDPT: bits [38:30] */
    shifted = va >> 30;
    pdpt = shifted & 0x1FF;
    seq_printf(m, "PDPT: 0x%lx >> 30 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pdpt);

    /* PD: bits [29:21] */
    shifted = va >> 21;
    pd = shifted & 0x1FF;
    seq_printf(m, "PD:   0x%lx >> 21 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pd);

    /* PT: bits [20:12] */
    shifted = va >> 12;
    pt = shifted & 0x1FF;
    seq_printf(m, "PT:   0x%lx >> 12 = 0x%lx → & 0x1FF = %lu\n", va, shifted, pt);

    /* Offset: bits [11:0] */
    off = va & 0xFFF;
    seq_printf(m, "OFF:  0x%lx & 0xFFF = %lu (0x%lx)\n\n", va, off, off);
}

static int indices_show(struct seq_file* m, void* v) {
    int i;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 02: PAGE TABLE INDEX EXTRACTION\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "FORMULA:\n");
    seq_printf(m, "  PML4 = (VA >> 39) & 0x1FF\n");
    seq_printf(m, "  PDPT = (VA >> 30) & 0x1FF\n");
    seq_printf(m, "  PD   = (VA >> 21) & 0x1FF\n");
    seq_printf(m, "  PT   = (VA >> 12) & 0x1FF\n");
    seq_printf(m, "  OFF  = VA & 0xFFF\n\n");

    for (i = 0; i < NUM_VADDRS; i++) {
        show_extraction(m, test_vaddrs[i]);
    }

    return 0;
}

static int indices_open(struct inode* inode, struct file* file) {
    return single_open(file, indices_show, NULL);
}

static const struct proc_ops indices_ops = {
    .proc_open = indices_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init indices_init(void) {
    proc_create("demo_indices", 0444, NULL, &indices_ops);
    pr_info("demo_indices: loaded\n");
    return 0;
}

static void __exit indices_exit(void) {
    remove_proc_entry("demo_indices", NULL);
    pr_info("demo_indices: unloaded\n");
}

module_init(indices_init);
module_exit(indices_exit);
