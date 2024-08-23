#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

static int len, temp;
static char *msg;

ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp );
ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp);
void create_new_proc_entry(void);
int proc_init(void);
void proc_cleanup(void);

ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp ) {
    long not_copied;
    if (count > temp) {
        count = temp;
    }
    temp = temp - count;
    not_copied = copy_to_user(buf, msg, count);
    if (not_copied != 0) {
        printk(KERN_INFO "%ld bytes could not be copied to user.\n", not_copied);
    }
    if (count == 0) {
        temp = len;
    }
    return count;
}
 
ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp) {
    long not_copied;
    if (!msg) {
        printk(KERN_ERR "Memory allocation failed.\n");
        return -ENOMEM;
    }
    msg = krealloc(msg, count * sizeof(char), GFP_KERNEL);
    not_copied = copy_from_user(msg, buf, count);
    if (not_copied != 0) {
        printk(KERN_INFO "%ld bytes could not be copied from user.\n", not_copied);
    }
    len = count;
    temp = len;
    return count;
}
 
static const struct proc_ops proc_fops = {
    .proc_read = read_proc,
    .proc_write = write_proc,
};
 
void create_new_proc_entry(void) {
    proc_create("proc", 0, NULL, &proc_fops);
    msg = kmalloc(sizeof(char), GFP_KERNEL);
}
 
int proc_init(void) {
    create_new_proc_entry();
    return 0;
}
 
void proc_cleanup(void) {
    remove_proc_entry("proc", NULL);
    kfree(msg);
}
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgen");
module_init(proc_init);
module_exit(proc_cleanup);