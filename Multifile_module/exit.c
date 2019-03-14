#include <linux/kernel.h>	
#include <linux/module.h>	

void cleanup_module()
{
	printk(KERN_INFO "Few.. Just got out of module\n");
}