#include "../Network.h"
#define DEBUG 1 
void Network::receiveData(void)
{

#if DEBUG
	std::cout << "Handling client ";
    try{std::cout << m_socket->getForeignAddress() << ": ";}
    catch (SocketException e){std::cerr << "Unable to get foreign address" << endl;}
    try{cout << m_socket->getForeignPort() << endl;}
    catch (SocketException e){cerr << "Unable to get foreign port" << endl;}

#endif    
    
    // Send received string and receive again until the end of transmission
    char buffer[RCVBUFSIZE];
    int recvMsgSize;
    memset(buffer, 0, RCVBUFSIZE); //clearing the buffer for next time
    while ((recvMsgSize = sock->recv(buffer, RCVBUFSIZE)) > 0) //Zero means end of transmission
    {
        cout<<"Server received: "<<buffer<<endl
        
    }
    delete sock;
}

void Network::sendData(void)
{
	std::string data=m_out_buffer.receiveData();

	sock->send(data, data.length());
}
