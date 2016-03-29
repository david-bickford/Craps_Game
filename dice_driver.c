/* 
 * File:   dice_driver.c
 * Author: David Bickford
 * Email: drb56@pitt.edu
 *
 */
//various imports used
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>


/* get_random_byte function given by Dr.Misurda
 */
unsigned char get_random_byte(int max)
{
     unsigned char c;
     get_random_bytes(&c, 1);
     return c%max;
}

/* dice_read function to call get_random_byte and setting its return value to
 * an unsigned char. Then sets that char to the buffer.
 * 
 * @param: struct *file, char *buf, size_t count
 * @return: ssize_t
 */
static ssize_t dice_read(struct file * file, char * buf, size_t count)
{
    //calling get_random_byte and setting the value to a char
    unsigned char c = get_random_byte(5);
    copy_to_user(buf, &c, 1);
    //returning 1
    return 1;
}
//struct for calling read and owner
static const struct file_operations dice_fops = 
{
        .owner		= THIS_MODULE,
        .read		= dice_read,
};
//struct to find a minor number and name it dice
static struct miscdevice dice_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/dice.
	 */
	"dice",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&dice_fops
};

/* init function for when you're coming in first time.
 */
static int __init
dice_init(void)
{
	int ret;
	ret = misc_register(&dice_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"dice\" misc device\n");

	return ret;
}

module_init(dice_init);

/* exit function for when you're leaving function
 */
static void __exit
dice_exit(void)
{
	misc_deregister(&dice_dev);
}

module_exit(dice_exit);

//modules for license, author, description, and version
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Bickford <drb56@pitt.edu>");
MODULE_DESCRIPTION("\"dice\" minimal module");
MODULE_VERSION("dev");
