#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/init.h>		

static int __init hello_world_init(void)
{
	printk(KERN_INFO "Yay! We'r inside kernel 1.\n");
	return 0;
}

static void __exit hello_world_exit(void)
{
	printk(KERN_INFO "Few.. Just got out of module 1.\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);