//
//  Server.hpp
//  
//
//  Created by Stephanie Smith on 3/20/16.
//
//
#define BAUDRATE 9600 // default baudrate
#define BUF_MAX 256   // default max buffer size
#define TIMEOUT 5000 // default timeout


#ifndef Server_hpp
#define Server_hpp

#define DEBUG 1 //will print off info

#include <stdio.h>

#endif /* Server_hpp */

class Server
{
    public:
        Server(const int port)
    
    
        void handleClient();
    
        char* testArduinoConnection();
        char* writeToMotors();
        char* requestArduinoData();
    
        char* requestImages();
        void moveCamera();
    
    private:
        char m_buffer[BUF_MAX]; //can hold 256 bytes
        const char* m_serialport="/dev/cu.usbmodem1411"; //default for stephanie's laptop
        const short m_desLength=2;
        TCPSocket m_sock;
        unsigned short m_servPort;
        const int serial_fd;
    
         int arduinoInit();
    
        //and utility functions
    
};
