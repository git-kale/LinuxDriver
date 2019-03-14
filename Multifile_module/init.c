#include <linux/kernel.h>
#include <linux/module.h>	

int init_module(void)
{
	printk(KERN_INFO "Yay! We'r inside kernel\n");
	return 0;
}