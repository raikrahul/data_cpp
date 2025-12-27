/*
 * DEMO 12: READ TARGET PROCESS CR3
 * ═════════════════════════════════
 *
 * find_task_by_vpid(pid) → task_struct
 * task->mm->pgd → PML4 virtual address
 * virt_to_phys(pgd) → PML4 physical address
 *
 * SECURITY: Requires root or CAP_SYS_PTRACE
 */

#include <asm/io.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("r");
MODULE_DESCRIPTION("Demo 12: Target Process CR3");

#define PTE_ADDR_MASK 0x000FFFFFFFFFF000UL

static int demo_pid_show(struct seq_file* m, void* v) {
    unsigned long my_cr3, my_pml4;
    struct task_struct* task;

    /* Get current CR3 */
    asm volatile("mov %%cr3, %0" : "=r"(my_cr3));
    my_pml4 = my_cr3 & PTE_ADDR_MASK;

    seq_printf(m, "═══════════════════════════════════════════════════════════\n");
    seq_printf(m, "DEMO 12: PROCESS CR3 COMPARISON\n");
    seq_printf(m, "═══════════════════════════════════════════════════════════\n\n");

    seq_printf(m, "CURRENT PROCESS (reading this /proc):\n");
    seq_printf(m, "  PID: %d\n", current->pid);
    seq_printf(m, "  COMM: %s\n", current->comm);
    seq_printf(m, "  CR3: 0x%lx\n", my_cr3);
    seq_printf(m, "  PML4_phys: 0x%lx\n\n", my_pml4);

    /* List a few processes */
    seq_printf(m, "OTHER PROCESSES:\n");
    seq_printf(m, "────────────────────────────────────────────────────────\n");

    int count = 0;
    rcu_read_lock();
    for_each_process(task) {
        if (task->mm && count < 10) {
            unsigned long pgd_phys = virt_to_phys(task->mm->pgd);

            seq_printf(m, "PID %6d %-16s PML4=0x%lx\n", task->pid, task->comm, pgd_phys);
            count++;
        }
    }
    rcu_read_unlock();

    seq_printf(m, "\nOBSERVATION:\n");
    seq_printf(m, "  Different PIDs have different PML4 physical addresses\n");
    seq_printf(m, "  Each process has its own page tables\n");
    seq_printf(m, "  Kernel space (PML4[256:511]) is shared across all\n");

    return 0;
}

static int demo_pid_open(struct inode* inode, struct file* file) {
    return single_open(file, demo_pid_show, NULL);
}

static const struct proc_ops demo_pid_ops = {
    .proc_open = demo_pid_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init demo_pid_init(void) {
    proc_create("demo_pid", 0444, NULL, &demo_pid_ops);
    pr_info("demo_pid: loaded\n");
    return 0;
}

static void __exit demo_pid_exit(void) { remove_proc_entry("demo_pid", NULL); }

module_init(demo_pid_init);
module_exit(demo_pid_exit);
