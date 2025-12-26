/*
 * asid_driver.c - Kernel module to expose ASID/PCID info via /proc/asid_info
 *
 * Shows CR3, CR4, PCID status for the calling process.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("example");
MODULE_DESCRIPTION("Expose ASID/PCID info via /proc/asid_info");
MODULE_VERSION("0.1");

/*
 * READ CR3:
 * CR3 = Control Register 3 = Page Directory Base Register
 * Contains physical address of PML4 table + PCID (if enabled)
 */
static inline unsigned long read_cr3(void) {
    unsigned long val;
    asm volatile("mov %%cr3, %0" : "=r"(val));
    return val;
}

/*
 * READ CR4:
 * CR4 = Control Register 4 = CPU feature control
 * Bit 17 = PCIDE = Process Context ID Enable
 */
static inline unsigned long read_cr4(void) {
    unsigned long val;
    asm volatile("mov %%cr4, %0" : "=r"(val));
    return val;
}

/*
 * CPUID: Get CPU feature flags
 * EAX=1 returns feature flags in ECX/EDX
 * ECX bit 17 = PCID available (hardware support)
 */
static inline void do_cpuid(unsigned int eax_in, unsigned int* a, unsigned int* b, unsigned int* c,
                            unsigned int* d) {
    unsigned int eax = eax_in, ebx, ecx, edx;
    asm volatile("cpuid" : "+a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : : "memory");
    if (a) *a = eax;
    if (b) *b = ebx;
    if (c) *c = ecx;
    if (d) *d = edx;
}

static int asid_show(struct seq_file* m, void* v) {
    unsigned long cr3 = read_cr3();
    unsigned long cr4 = read_cr4();
    unsigned long pml4_phys = cr3 & 0x000FFFFFFFFFF000UL; /* Bits [51:12] */
    unsigned long asid_low = cr3 & 0xFFFUL;               /* Bits [11:0] = PCID */
    unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;
    const int has_mm = (current->mm != NULL);
    const int pcide_enabled = !!(cr4 & (1UL << 17));

    do_cpuid(1, &eax, &ebx, &ecx, &edx);
    const int pcid_hw_support = !!(ecx & (1u << 17));

    seq_printf(m, "═══════════════════════════════════════════════════════════════\n");
    seq_printf(m, "ASID/PCID INFO FOR CURRENT PROCESS\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════════\n");
    seq_printf(m, "\n");
    seq_printf(m, "PROCESS:\n");
    seq_printf(m, "  PID  = %d\n", task_pid_nr(current));
    seq_printf(m, "  COMM = %s\n", current->comm);
    seq_printf(m, "  Has mm_struct = %s\n", has_mm ? "YES" : "NO (kernel thread)");
    seq_printf(m, "\n");

    seq_printf(m, "CR3 REGISTER:\n");
    seq_printf(m, "  CR3 raw        = 0x%016lx\n", cr3);
    seq_printf(m, "  PML4 physical  = 0x%016lx (bits [51:12])\n", pml4_phys);
    seq_printf(m, "  Low 12 bits    = 0x%03lx = %lu decimal\n", asid_low, asid_low);
    seq_printf(m, "\n");

    seq_printf(m, "CR4 REGISTER:\n");
    seq_printf(m, "  CR4 raw        = 0x%016lx\n", cr4);
    seq_printf(m, "  CR4.PCIDE      = %d (bit 17)\n", pcide_enabled);
    seq_printf(m, "\n");

    seq_printf(m, "CPUID (EAX=1):\n");
    seq_printf(m, "  ECX            = 0x%08x\n", ecx);
    seq_printf(m, "  PCID HW support= %d (ECX bit 17)\n", pcid_hw_support);
    seq_printf(m, "\n");

    seq_printf(m, "INTERPRETATION:\n");
    if (pcid_hw_support && pcide_enabled) {
        seq_printf(m, "  → PCID ENABLED: Low 12 bits of CR3 = PCID = %lu\n", asid_low);
        seq_printf(m, "  → TLB entries tagged with PCID, no flush on CR3 switch\n");
    } else if (pcid_hw_support && !pcide_enabled) {
        seq_printf(m, "  → PCID AVAILABLE but DISABLED (CR4.PCIDE=0)\n");
        seq_printf(m, "  → Low 12 bits of CR3 = reserved/flags (should be 0)\n");
        seq_printf(m, "  → TLB FLUSHES on every CR3 switch\n");
    } else {
        seq_printf(m, "  → NO PCID SUPPORT (AMD or old Intel)\n");
        seq_printf(m, "  → Low 12 bits = reserved (should be 0)\n");
        seq_printf(m, "  → TLB FLUSHES on every CR3 switch\n");
    }
    seq_printf(m, "═══════════════════════════════════════════════════════════════\n");

    return 0;
}

static int asid_open(struct inode* inode, struct file* file) {
    return single_open(file, asid_show, NULL);
}

static const struct proc_ops asid_fops = {
    .proc_open = asid_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init asid_init(void) {
    proc_create("asid_info", 0444, NULL, &asid_fops);
    printk(KERN_INFO "asid_driver: Loaded. Read /proc/asid_info\n");
    return 0;
}

static void __exit asid_exit(void) {
    remove_proc_entry("asid_info", NULL);
    printk(KERN_INFO "asid_driver: Unloaded\n");
}

module_init(asid_init);
module_exit(asid_exit);
