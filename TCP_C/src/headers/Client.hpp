//
//  Client.hpp
//  
//
//  Created by Stephanie Smith on 2/28/16.
//  add class template
//

#ifndef Client_hpp
#define Client_hpp

#define DEBUG 1

#include <stdio.h>
#include <string.h>           // For user inputs
#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include <iostream>           // For cerr and cout

#endif /* Client_hpp */

class Client
{
    public:
    
        Client(const std::string servAddress, unsigned short servPort);
        bool sendToServer(std::string);
        void echoMessage(unsigned int bufferSize);
        std::string receiveMessageFromServer(unsigned int bufferSize);
    
        /*getters/setters-->implemented here!*/
        std::string getServerIP(){return m_servAddress;}
        unsigned short getServerPort(){return m_servPort;}
        void setServerIP(string servAddress){m_servAddress=servAddress;}
        void setServerPort(unsigned short servPort){m_servPort=servPort;}

    private:
        TCPSocket* m_sock; //open socket
        std::string m_servAddress;
        unsigned short m_servPort;

};
#if DEBUG
    int main(void)
    {
        //Client client("127.0.0.1", 1024);
        return 0;
    }
#endif

