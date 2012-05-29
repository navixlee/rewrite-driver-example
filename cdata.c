/*
 * =====================================================================================
 *
 *       Filename:  cdata.c
 *
 *    Description:  linux device driver for study.
 *
 *        Version:  1.0
 *        Created:  05/29/2012 05:41:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  navi,navi 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <asm/io.h>
#include <asm/uaccess.h>


#define DEV_NAME  "cdata"

static unsigned int dev_major = 0;
module_param(dev_major, uint, 0);


static int cdata_open(struct inode *inode, struct file *filp)
{
	int i;

	printk(KERN_INFO "CDATA: is opened !!\n");

	for(i = 0; i < 500000; i++){
		printk(KERN_INFO "CDATA: for-loop=%d !!\n",i);
                schedule();
	}

	return 0; 
}

ssize_t cdata_write(struct file *filp, const char *buf, size_t size,loff_t *off)
{
	return 0;
}

int cdata_close(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "CDATA: is closed ~~\n");
	return 0;
}

static struct file_operations cdata_fops = {
	open:	 cdata_open,
     release:	cdata_close,
       write:	cdata_write, 
};

int cdata_init_module(void)
{
	if(register_chrdev(dev_major, DEV_NAME, &cdata_fops) < 0){
		printk(KERN_INFO "CDATA: can't register driver\n"); 
       		return -1;
	}
 	printk(KERN_INFO "CDATA.ko initialed.\n");
	return 0;
}

void cdata_cleanup_module(void)
{
	unregister_chrdev(dev_major, DEV_NAME);
 	printk(KERN_INFO "CDATA.ko cleanup.\n");
}

module_init(cdata_init_module);
module_exit(cdata_cleanup_module);

MODULE_LICENSE("GPL");
