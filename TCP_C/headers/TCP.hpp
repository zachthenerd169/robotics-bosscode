//
//  TCP.hpp
//  
//
//  Created by Stephanie Smith on 2/28/16.
//
//

#ifndef TCP_hpp
#define TCP_hpp

#include <stdio.h>

#endif /* TCP_hpp */

class TCP
{
    public:
        void displayMainMenu();
        void displayRobotControlMenu();
        void handleClient(TCPSocket *sock, int fd);
        void handleServer();
        boolean processMainMenuInput();
        boolean processRCMenuInput();
    
    private:
        Client client;
        Server server;
    
}
