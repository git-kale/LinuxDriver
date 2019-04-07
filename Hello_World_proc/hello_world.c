#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define DRIVER_AUTHOR "Mahesh Kale (github/git-kale)"
#define DRIVER_DESC "Hello Message from /proc"

static int hello_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "Hello World from /proc/hello_world!\n");
	return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, hello_proc_show, NULL);
}

static const struct file_operations hello_proc_fops = {
	.owner = THIS_MODULE,
	.open = hello_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init hello_proc_init(void)
{
	printk(KERN_INFO "Yay! We'r inside kernel\n");
	proc_create("hello_proc", 0, NULL, &hello_proc_fops);
	return 0;
}

static void __exit hello_proc_exit(void)
{
	printk(KERN_INFO "Few.. Just got out of module\n");
	remove_proc_entry("hello_proc", NULL);
}

MODULE_LICENSE("GPL");
module_init(hello_proc_init);
module_exit(hello_proc_exit);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);