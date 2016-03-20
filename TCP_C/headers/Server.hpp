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
        TCPSocket m_sock;
        unsigned short m_servPort;
        const int serial_fd;
    
         int arduinoInit();
    
        //and utility functions
    
};
