//
//  Client.c
//
//  Created by Stephanie Smith on 1/12/16.
//  User will use to program to communicate with the NUC on the robot
//  compile: gcc -o Client.exe Client.c
//  run: ./Client.exe

#include "Client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
    int tcpSocket; //will hold the created socket
    struct sockaddr_in sAddr; //used to define the client port
    struct hostent *hostInfo; //used to define host
    const int maxBuff = 256;
    char messageBuff[maxBuff];
    char* serverIP;
}