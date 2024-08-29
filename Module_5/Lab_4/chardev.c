#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgen");

static int __init chardev_init(void);
static void __exit chardev_exit(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 100

module_init(chardev_init);
module_exit(chardev_exit);

static struct class *cls;
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release,
};

static int major;
static char msg[BUF_LEN];
static struct class* cls;
static int busy = 0;

static int __init chardev_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        pr_alert("Driver registration failed\n");
        return major;
    }
    pr_info("Driver registered (major: %d)\n", major);

    cls = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    return SUCCESS;
}

static void __exit chardev_exit(void) {
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    unregister_chrdev(major, DEVICE_NAME);
    pr_info("Driver unregistered (major: %d)\n", major);
}

static int device_open(struct inode *inode, struct file *file) {
    if (busy != 0) {
        return -EBUSY;
    }
    busy = 1;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
    busy = 0;
    module_put(THIS_MODULE);
    return SUCCESS;
}

static ssize_t device_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset) {
    int bytes_read = 0;
    const char *msg_ptr = msg;
    if (!*(msg_ptr + *offset)) {
        *offset = 0;
        return 0;
    }
    msg_ptr += *offset;
    while (length && *msg_ptr) {
        put_user(*(msg_ptr++), buffer++);
        length--;
        bytes_read++;
    }
    *offset += bytes_read;
    return bytes_read;
}

static ssize_t device_write(struct file *filp, const char __user *buff, size_t len, loff_t *off) {
    if (len >= BUF_LEN) {
        len = BUF_LEN - 1;
    }
    if (copy_from_user(msg, buff, len)) {
        return -EFAULT;
    }
    msg[len] = '\0';
    return len;
}