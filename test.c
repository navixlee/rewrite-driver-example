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

int main(void)
{
    int fd;

    fd = open("/dev/cdata", O_RDWR);
    close(fd);
}


