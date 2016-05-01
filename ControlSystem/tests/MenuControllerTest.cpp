#include "../lib/PracticalSocket.h"
#include "../MenuController.h"
#include <iostream>
#include <string.h>
#include <memory>

int main (void)
{
    //MenuController m;
    MenuController menu("127.0.0.1", 1024);

	//TCPServerSocket* socket = new TCPServerSocket(1024);

     //std::shared_ptr<TCPServerSocket> socket;

     //std::shared_ptr<TCPServerSocket> socket2(new TCPServerSocket(1024));
	 //socket=socket2;

    //TCPServerSocket* sock = new TCPServerSocket(1026);
    //TCPServerSocket* sock2=&(sock(1025));
   
     

	//socket(new TCPServerSocket(1024));

	 //TCPServerSocket* socket;
	 //socket=new TCPServerSocket(1024);

	//TCPServerSocket socket2=socket(1025);

	std::cout<< sock->getLocalPort() <<std::endl;
	std::cout<< sock2->getLocalPort() <<std::endl;
    return 0;
}

