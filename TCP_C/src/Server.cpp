//
//  Server.cpp
//  
//
//  Created by Stephanie Smith on 3/20/16.
//
//

#include "Server.hpp"


Server::Server(const int port) //constructor
{
    m_servPort=port;
    serial_fd=arduinoInit(); //initialze communication with arduino
    
    TCPServerSocket servSock(servPort); //ServerSocket object
    cout<<"server running on port: "<<m_servPort<<endl;
    while(true){handleClient(servSock.accept(), fd);}  //Wait for a client to connect
}
void Server::handleClient()
{
    std::cout << "Handling client "; //getting ip and port of client
    try{std::cout << m_sock->getForeignAddress() << ": ";}
    catch (SocketException e){std::cerr << "Unable to get foreign address" << std::endl;}
    
    try{std::cout << m_sock->getForeignPort() << std::endl;}
    catch (SocketException e){std::cerr << "Unable to get foreign port" << std::endl;}
    
    memset(m_buffer, 0, BUF_MAX); //clearing the buffer before a new chunk of data is received
    int recvMsgSize=0;
    
    //while the server has data to receive, receive it
    while ((recvMsgSize = m_sock->recv(m_buffer, RCVBUFSIZE)) > 0) //Zero means end of transmission
    {
        
        #if DEBUG
            std::cout<<"Server received: "<<m_buffer<<std::endl;
        #endif
        string full_str = string(m_buffer); //casting char* to string type, so we can parse the string easily
        string des=full_str.substr(0, m_desLength); //des is what device the message was intended for.
                                               //des should ALWAYS be specified with 1 character followed by a -
                                               //des could be:
                                                    //a- (for controlling motors)
                                                    //c- (for getting image data)
                                                    //m- (for only client server message-->used for testing)
        const char* message=full_str.substr(m_desLength, recvMsgSize).c_str(); //removing the "des-" part of the string & then converting the str back into a C string, so we can use the arduino-serial/PracticalSocket libraries
        if(des.compare("a-")==0) //message for either arduino
        {
            parseArdCommand(string(message));
        }
        else if(des.compare("c-")==0) //message for camera --> take pic and highlight certain data from the image
        {
            parseCamCommand(string(message));
        }
        else if(des.compare("m-")==0) //send message back to client
        {
            m_sock->send(message, recvMsgSize);
        }
        else
        {
            #if DEBUG
                std::cout<<"message desination could not be specified"<<std::endl;
            #endif
        }
    }
    delete m_sock; //done with the socket, so you can delete it
}
/**
 //24 bits for one way
 *1- -->arduino that controls the robot motors
 * 2- -->arduino that controls the camera
 **/
void Server::parseArdCommand(string message)
{
    string des=message.substr(0,m_desLength);
    if(des.compare("1-")==0)
    {
        message.substr(m_desLength, message.length())
        vector<string> ard_control=splitString(message); //break up the line
        short mode=-1;
        short powerLevel-1;
        
        writeToRobotMotors();
    }
    else if(des.compare("2-"))
    {
        writeToCamMotors();
    }
    else
    {
        #if DEBUG
            std::cout<<"arduino function could not be specified"<<std::endl;
        #endif
    }
}
void Server::writeToRobotMotors()
{
}
void Server::writeToCamMotors()
{
}
void Server::parseCamCommand(string message)
{
}
void Server::testArduinoConnection()
{
}
char* Server::writeToMotors()
{
}
char* Server::requestArduinoData()
{
}
char* Server::requestImages()
{
}
void Server::moveCamera()
{
}
int Server::arduinoInit()
{
    fd = serialport_init(m_serialport, BAUDRATE); //opening port
    (fd == -1) ? std::cout<< "couldn't open port" << std::endl : std::cout<< "opened port " << m_serialport <<std::endl;
        serialport_flush(fd);
        return fd;
}
