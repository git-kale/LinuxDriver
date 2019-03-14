#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "Mahesh Kale (github/git-kale)"
#define DRIVER_DESC "Hello Message"

static int __init init_hello_world(void)
{
    printk(KERN_INFO "Yay! We'r inside kernel\n");
	return 0;
}

static void __exit cleanup_hello_world(void)
{
    printk(KERN_INFO "Few.. Just got out of module\n");
}

module_init(init_hello_world);
module_exit(cleanup_hello_world);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("Turing Machine");