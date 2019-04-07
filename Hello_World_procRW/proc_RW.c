#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#define BUFSIZE 100

#define DRIVER_AUTHOR "Mahesh Kale (github/git-kale)"
#define DRIVER_DESC "I/O in /proc filesystem"

static int from = 100;
module_param(from, int, 0660);

static int got = 0;
module_param(got, int, 0660);

static struct proc_dir_entry *ent;

static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
    int num, c, i, m;
    
    char buf[BUFSIZE];
    if (*ppos > 0 || count > BUFSIZE)
        return -EFAULT;
    if (copy_from_user(buf, ubuf, count))
        return -EFAULT;
    num = sscanf(buf, "%d/%d", &m, &i);
    if (num != 2)
        return -EFAULT;
    from = i;
    got = m;
    c = strlen(buf);
    *ppos = c;
    return c;
}

static ssize_t myread(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
    char buf[BUFSIZE];
    int len = 0;
    if (*ppos > 0 || count < BUFSIZE)
        return 0;
    len += sprintf(buf, "Total Marks = %d\n", from);
    len += sprintf(buf + len, "Marks Obtained = %d\n", got);

    if (copy_to_user(ubuf, buf, len))
        return -EFAULT;
    *ppos = len;
    return len;
}

static struct file_operations myops =
    {
        .owner = THIS_MODULE,
        .read = myread,
        .write = mywrite,
};

static int simple_init(void)
{
    printk(KERN_INFO "Yay! We'r inside kernel\n");
    ent = proc_create("proc_rw", 0660, NULL, &myops);
    return 0;
}

static void simple_cleanup(void)
{
    printk(KERN_INFO "Few.. Just got out of module\n");
    proc_remove(ent);
}

MODULE_LICENSE("GPL");
module_init(simple_init);
module_exit(simple_cleanup);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);