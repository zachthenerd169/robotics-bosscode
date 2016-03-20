//
//  Client.hpp
//  
//
//  Created by Stephanie Smith on 2/28/16.
//  add class template
//

#ifndef Client_hpp
#define Client_hpp

#include <stdio.h>
#include <string.h>           // For user inputs
#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include <iostream>           // For cerr and cout

#endif /* Client_hpp */

class Client
{
    public:
    
        Client(const string servAddress, unsigned short servPort):m_servAddress(servAddress), m_servPort(servPort), m_sock(servAddress, servPort){} //initializer list

        /*For the command-line interface there are three different types of
         menus to be dispayed*/
    
        //MAYBE MAKE MENU CLASS?
        void displayMainMenu(); //debug commands, change IP/port, control robot, control via Xbox Controller
        void displayRobotMenu(); //to send commands to the robot (controlling motors)
        void displayRequestMenu(); //to request info from the robot
    
        /*sending/receiving*/
        bool sendToServer(const char* message);
        void echoMessage(unsigned int bufferSize);
        string receiveMessageFromServer(unsigned int bufferSize);
    
        /*getters/setters-->implemented here!*/
        short getMenuSelection(){return m_numInput;}
        string getServerIP(){return m_servAddress;}
        unsigned short getServerPort(){return m_servPort;}
        void setMenuSelection(int numInput){m_numInput=numInput;}
        void setServerIP(string servAddress){m_servAddress=servAddress;}
        void setServerPort(unsigned short servPort){m_servPort=servPort;}

    private:
        TCPSocket m_sock; //open socket
        string m_servAddress;
        unsigned short m_servPort;
        short m_numInput;
        string m_strInput;
};
