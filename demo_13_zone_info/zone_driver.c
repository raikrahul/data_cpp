/*
 * DEMO 13: ZONE INFORMATION (SIMPLIFIED)
 * ======================================
 *
 * WHAT THIS DRIVER DOES:
 * Reads and displays memory zone information from exported kernel data.
 * Uses simple global variables instead of unexported iterators.
 *
 * YOUR MACHINE ZONE DATA:
 *   Total present: 4,042,587 pages × 4 KB = 15.43 GB
 *   Total managed: 3,944,069 pages × 4 KB = 15.04 GB
 */

#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 13: Memory Zone Information");

static int zone_info_show(struct seq_file* m, void* v) {
    struct sysinfo si;
    unsigned long total_pages, free_pages;

    si_meminfo(&si);
    total_pages = si.totalram;
    free_pages = si.freeram;

    seq_printf(m, "═══════════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 13: MEMORY INFORMATION\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "ZONE PURPOSES (from architecture):\n");
    seq_printf(m, "  DMA:     0 - 16 MB (ISA devices, legacy)\n");
    seq_printf(m, "  DMA32:   0 - 4 GB (32-bit PCI devices)\n");
    seq_printf(m, "  Normal:  4 GB - end (no restrictions)\n");
    seq_printf(m, "  Movable: hotplug memory (if configured)\n");
    seq_printf(m, "  Device:  persistent memory (if installed)\n\n");

    seq_printf(m, "PAGE SIZE: %lu bytes (%lu KB)\n\n", PAGE_SIZE, PAGE_SIZE / 1024);

    seq_printf(m, "MEMORY STATISTICS:\n");
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");
    seq_printf(m, "Total RAM:     %lu pages = %lu MB\n", total_pages,
               (total_pages * PAGE_SIZE) / (1024 * 1024));
    seq_printf(m, "Free RAM:      %lu pages = %lu MB\n", free_pages,
               (free_pages * PAGE_SIZE) / (1024 * 1024));
    seq_printf(m, "Used RAM:      %lu pages = %lu MB\n", total_pages - free_pages,
               ((total_pages - free_pages) * PAGE_SIZE) / (1024 * 1024));
    seq_printf(m, "Shared:        %lu pages\n", si.sharedram);
    seq_printf(m, "Buffer:        %lu pages\n", si.bufferram);
    seq_printf(m, "Total Swap:    %lu pages\n", si.totalswap);
    seq_printf(m, "Free Swap:     %lu pages\n", si.freeswap);
    seq_printf(m, "High Memory:   %lu pages\n", si.totalhigh);
    seq_printf(m, "Memory Unit:   %u bytes\n", si.mem_unit);

    seq_printf(m, "\nCALCULATIONS:\n");
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");
    seq_printf(m, "Total RAM in bytes: %lu × %lu = %lu\n", total_pages, PAGE_SIZE,
               total_pages * PAGE_SIZE);
    seq_printf(m, "Total RAM in MB:    %lu / (1024 × 1024) = %lu MB\n", total_pages * PAGE_SIZE,
               (total_pages * PAGE_SIZE) / (1024 * 1024));
    seq_printf(m, "Total RAM in GB:    %lu / (1024 × 1024 × 1024) = %lu.%02lu GB\n",
               total_pages * PAGE_SIZE, (total_pages * PAGE_SIZE) / (1024UL * 1024 * 1024),
               ((total_pages * PAGE_SIZE) % (1024UL * 1024 * 1024)) * 100 / (1024UL * 1024 * 1024));

    seq_printf(m, "\nBUDDY ALLOCATOR:\n");
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");
    seq_printf(m, "Max contiguous allocation depends on kernel config\n");
    seq_printf(m, "Typically 2^10 = 1024 pages = 4 MB max contiguous\n");

    seq_printf(m, "\nNUMA:\n");
    seq_printf(m, "───────────────────────────────────────────────────────────────\n");
    seq_printf(m, "NUMA nodes: check /sys/devices/system/node/\n");
    seq_printf(m, "Your machine: Node 0 only (not NUMA)\n");

    return 0;
}

static int zone_info_open(struct inode* inode, struct file* file) {
    return single_open(file, zone_info_show, NULL);
}

static const struct proc_ops zone_info_ops = {
    .proc_open = zone_info_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init zone_info_init(void) {
    proc_create("demo_zones", 0444, NULL, &zone_info_ops);
    pr_info("demo_zones: module loaded. Read /proc/demo_zones\n");
    return 0;
}

static void __exit zone_info_exit(void) {
    remove_proc_entry("demo_zones", NULL);
    pr_info("demo_zones: module unloaded\n");
}

module_init(zone_info_init);
module_exit(zone_info_exit);
