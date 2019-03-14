#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
	printk(KERN_INFO "Yay! We'r inside kernel 1.\n");
	return 0;
}
void cleanup_module(void)
{
	printk(KERN_INFO "Few.. Just got out of module 1.\n");
}