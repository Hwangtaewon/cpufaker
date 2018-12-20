
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/desc.h>
#include <asm/pgtable.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/highmem.h>
#include <linux/preempt.h>
#include <asm/topology.h>
#include <linux/kthread.h>
#include <linux/kernel_stat.h>
#include <linux/percpu-defs.h>
#include <linux/smp.h>
#include <linux/delay.h>

int thread1(void *data)
{
	int cpu_id;
	int i;
	while(1)
	{
		cpu_id = smp_processor_id();

	

		__this_cpu_write(kernel_cpustat.cpustat[CPUTIME_USER],0);
		__this_cpu_write(kernel_cpustat.cpustat[CPUTIME_SYSTEM],0);
		current->se.sum_exec_runtime=0;
		

		msleep(1);
	}	

	return 0;
}

int thread2(void *data)
{
	int cpu_id;
	int i;
	while(1)
	{
		cpu_id = smp_processor_id();

	

		__this_cpu_write(kernel_cpustat.cpustat[CPUTIME_USER],0);
		__this_cpu_write(kernel_cpustat.cpustat[CPUTIME_SYSTEM],0);
		current->se.sum_exec_runtime=0;
		
	
		for(i=0;i<100;i++)
			printk("[%d].%d is working\n",cpu_id,i);
		msleep(1);
	}	

	return 0;
}

static int hello_init(void)
{
	struct task_struct *task1,*task2;

	task1 = kthread_create(thread1,NULL,"task1");
	task2 = kthread_create(thread2,NULL,"task2");
	
	if(task1 && task2)
	{
		kthread_bind(task1,0);
		kthread_bind(task2,1);
		wake_up_process(task1);
		wake_up_process(task2);
	}
	return 0;
}


static void hello_exit(void)
{

	printk("end module\n=========================================================\n");

}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");



