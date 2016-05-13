#include "../ThreaddedNetwork.h"

/* Constructor */
ThreaddedNetwork::ThreaddedNetwork(int servPort) :
  m_servSock(servPort)
{
  // start the new thread running 'inThreadUpdate'
  my_thread = std::thread(&ThreaddedNetwork::inThreadUpdate,this);
}

/* getNewMessages */
std::vector<std::string> ThreaddedNetwork::getNewMessages()
{
  // create a vector to fill with new messages
  std::vector<std::string> newMessages;
  // read new messages if there are any
  // --- maybe make this time out so that it doesn't wait forever
  while(!q_new_messages.empty())
  {
    // pop new messages into vector
    newMessages.push_back(q_new_messages.pop());
  }
  // return vector of new messages
  return newMessages;
}

bool ThreaddedNetwork::hasNewMessages()
{
  return !q_new_messages.empty();
}

void ThreaddedNetwork::inThreadUpdate()
{ 
  std::string currentMessage = "";
  char buffer[RCVBUFSIZE];
  int recvMsgSize;
  bool hasStart = false;
  while(true)
  {
    TCPSocket* sock = m_servSock.accept();
    std::cout <<"Got Connection\n";
    recvMsgSize = 1; // set to one just so we enter the loop
    while(recvMsgSize > 0)
    {
      // clear the input buffer
      memset(buffer, 0, RCVBUFSIZE);
      // get data from the socket
      recvMsgSize = sock->recv(buffer, RCVBUFSIZE);
      // iterate over the recieved data
      for(int i=0; i<recvMsgSize; i++)
      {
        // if we're recording a message
        if(hasStart)
        {
          // if this is the end of the message
          if(buffer[i] == ']')
          {
            // send the message to the main thread
            q_new_messages.push(currentMessage);
            // stop recording messages
            hasStart = false;
          }
          // if this is not the end of the message
          else
          {
            // add this character to the end of the current messsage
            currentMessage += buffer[i];
          }
        }
        // if we recieve a new start character
        if(buffer[i] == '[')
        {
          // start recording
          hasStart = true;
          // reset the current message
          currentMessage = "";
        } // end if
      } // end for
      sock->send(buffer,recvMsgSize);
    } // end while
    std::cout << "Closing connection\n";
    delete sock;
  } // end while
} // end inThreadUpdate
