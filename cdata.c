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

#include "cdata_ioctl.h"



#define DEV_NAME    "cdata"
#define DEV_MAJOR   121
/*  static unsigned int dev_major = 0;
module_param(dev_major, uint, 0);*/

struct cdata_t{
	unsigned long *fb;
};

static int cdata_open(struct inode *inode, struct file *filp)
{
	int minor;
	struct cdata_t *cdata;

	printk(KERN_INFO "(Ivan Lee)CDATA: is opened !!\n");
       
	minor = MINOR(inode->i_rdev);	
	printk(KERN_INFO "(Ivan Lee)minor number = %d.\n",minor);

	cdata = kmalloc(sizeof(struct cdata_t), GFP_KERNEL); 
	cdata->fb = ioremap(0x33f00000, 320*240*4);
        filp->private_data = (void*)cdata;
    	
	return 0; 
}

static ssize_t cdata_read(struct file *filp, char *buf, size_t size, loff_t *off)
{
	return 0;
}

static ssize_t cdata_write(struct file *filp, const char *buf, size_t size, loff_t *off)
{
	printk(KERN_INFO "(Ivan Lee)CDATA: Write!!\n"); 
	
	return 0;
}

static int cdata_close(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "(Ivan Lee)CDATA: is closed ~~\n");
	return 0;
}

static int cdata_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int n;
        unsigned long *fb;
	int i;
        struct cdata_t *cdata = (struct cdata_t *)filp->private_data;
	

	switch(cmd){
		case CDATA_CLEAR: {
			n = *((int *)arg);//FIXME:dirty
			printk(KERN_INFO "CDATA_CLEAR: %d pixels\n", n);
			//FIXME: Lock
			fb = cdata->fb;
                	//FIXME: Unlock
			for(i = 0; i < n; i++){
				writel(0x000000ff, fb + i);
			}
			break;
		}
	}
	return 0;
}

static int cdata_flush(struct file *filp)
{
	printk(KERN_INFO "(Ivan Lee)flush one time ^_^.\n");
	return 0;
}

static struct file_operations cdata_fops = {
	
	owner:      THIS_MODULE,
 	open:	    cdata_open,
	release:    cdata_close,
	write:	    cdata_write,
	read:	    cdata_read,
 	ioctl:      cdata_ioctl,
	flush:	    cdata_flush,		
};

static int cdata_init_module(void)
{
	unsigned long *fb;
        int i;

	if(register_chrdev(DEV_MAJOR, DEV_NAME, &cdata_fops) < 0){
		printk(KERN_INFO "(Ivan Lee)CDATA: can't register driver\n"); 
       		return -1;
	}

        fb = ioremap(0x33f00000, 320*240*4);/*remaping I/O memory adrress, physical address trans virtual address.*/
        
	for(i = 0; i < 320*240; i++){	
		writel(0x00ff0000, fb++);/*clear framebuffer to color of red.*/
	}

 	printk(KERN_INFO "(Ivan Lee)CDATA.ko initialed.\n");
	return 0;
}

static void cdata_cleanup_module(void)
{
	unregister_chrdev(DEV_MAJOR, DEV_NAME);
 	printk(KERN_INFO "(Ivan Lee)CDATA.ko cleanup.\n");
}

module_init(cdata_init_module);
module_exit(cdata_cleanup_module);

MODULE_LICENSE("GPL");
