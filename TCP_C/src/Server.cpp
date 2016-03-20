//
//  Server.cpp
//  
//
//  Created by Stephanie Smith on 3/20/16.
//
//

#include "Server.hpp"

Server::Server(const int port)
{
    m_servPort=port;
    serial_fd=arduinoInit();
    TCPServerSocket servSock(servPort); //ServerSocket object
    cout<<"server running on port: "<<m_servPort<<endl;
    while(true){handleClient(servSock.accept(), fd);}  //Wait for a client to connect
}
void Server::handleClient()
{
    cout << "Handling client ";
    try{cout << sock->getForeignAddress() << ": ";}
    catch (SocketException e){cerr << "Unable to get foreign address" << endl;}
    
    try{cout << sock->getForeignPort() << endl;}
    catch (SocketException e){cerr << "Unable to get foreign port" << endl;}
    
    // Send received string and receive again until the end of transmission
    char buffer[RCVBUFSIZE];
    int recvMsgSize;
    memset(buffer, 0, RCVBUFSIZE); //clearing the buffer for next time
    while ((recvMsgSize = sock->recv(buffer, RCVBUFSIZE)) > 0) //Zero means end of transmission
    {
        cout<<"Server received: "<<buffer<<endl;
        string str = string(buffer);
        if(str.substr(0,4).compare("ard-")==0) //see if it was a message intended for the arduino
        {
            str=str.substr(4, recvMsgSize);
            const char *message = str.c_str(); //stripping the 'ard-' off of the string
            cout<<"message: " << message<<endl;
            vector<string> ard_control=splitString(message); //break up the line
            int mode;
            int powerLevel;
            if(ard_control.size()==1|| ard_control.size() ==2 ) //if the arduino commands were correctly specified
            {
                mode = std::stoi(ard_control[0], nullptr, 10); //get the mode
                powerLevel = ard_control.size()==2 ? std::stoi(ard_control[1], nullptr, 10) : -1; //if no power level was specified send a -1 power
                char *ardMessage=writeToMotors(mode, powerLevel, fd); //write to the arduino
                cout<<"ARD MESSAGE: "<<message<<endl;
                sock->send(message, strlen(message)); //sending arduino message back to client
            }
            else{
                cout<<"after writeToArduino"<<endl;
                //else{cout<<"FIXX THIS!"<<endl;} don't need to do anything else
                sock->send(message, strlen(message)); //sending arduino message back to client
            }
            
        }
        else{sock->send(buffer, recvMsgSize);} //send message as is
    }
    delete sock; //done with the socket, so you can delete it
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
}
