/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  writen for test cdata.ko
 *
 *        Version:  1.0
 *        Created:  05/29/2012 07:36:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  navi, navi 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "cdata_ioctl.h"

int main(void)
{
	int   fd;
        int   i = 10000;
 	char p[] = {0x55};

	fd = open("/dev/cdata", O_RDWR);
	write(fd, p, 130);
	write(fd, p, 128);  
        //ioctl(fd, CDATA_CLEAR, &i);
	close(fd);
}


