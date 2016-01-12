//
//  Server.c
//  
//
//  Created by Stephanie Smith on 1/12/16.
//
//

#include <stdio.h>
#include <string.h>
#include "arduino-serial-lib.h"

int main(void)
{
    int baudrate = 9600; //default
    char* port="/dev/cu.usbmodem1411"; //default for stephanie's laptop
    int fd=-1; //status
    const char* test_message="hello arduino!";
    int rc; //status
    const int buf_max=256;
    char buf[buf_max];
    int timeout=5000; //default timeout
    char eolchar = '\n'; //when receive messages line by line
    
    printf("setting baud rate to %d\n", baudrate);
    printf("setting serial port to %s\n", port);
    
    fd = serialport_init(port, baudrate); //opening port
    fd==-1 ? perror("couldn't open port") : printf("opened port %s\n", port);
    serialport_flush(fd);
    
    fd==-1 ? perror("serial port not opened") : printf("sending message: %s\n", test_message); //sending test message
    
    rc = serialport_write(fd, test_message);
    if(rc==-1) perror("error writing");
    
    printf("receiving messages:\n");
    for(int i=0; i<2; i++) //two messages to read
    {
        if( fd == -1) perror("serial port not opened"); //receiving message sent    back by the arduino
        memset(buf,0,buf_max); //clearing buffer
        serialport_read_until(fd, buf, eolchar, buf_max, timeout);
        printf("%s", buf);
    }
    return 0;
}