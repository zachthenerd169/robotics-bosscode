//  Client.cpp
//  Created by Stephanie Smith on 1/13/16.
//
//  Description: client (the laptop running this code) will communicate
//  with the NUC (server) on the robot
//
//  To Compile: g++ -o Client.exe Client.cpp PracticalSocket.cpp
//  To Run: ./Client.exe 'Server's IP Address' 'Server's Port Number'

#include "PracticalSocket.h"  // For Socket and SocketException
#include "Client.hpp"
#include <iostream>           // For cerr and cout
#include <cstdlib>            // For atoi()
#include <string.h>           // For user inputs

//const int RCVBUFSIZE = 32;    // Size of receive buffer

bool confirm(char userConfirm, bool valid); //prototypes
int inputInt(void);

int main (int argc, char *argv[])
{
    
    if(argc!=3){cerr<<"\n\nError: Wrong Number of Arguments\nTo Run: "<< argv[0]<<" <Server's IP Address> <Server's Port>\n\n"<<endl;
        exit(1);} //imediately terminates if command line arguments were not specified
    
    bool done = true; //flag for main-menu do-while
    int userSelection=0; //user input for menu's
    char userConfirm;
    string servAddress=argv[1];
    unsigned short servPort = atoi(argv[2]);
    //char *message; //message client will send the server
    string tempMessage;
   
    //confirm input (don't know if I should keep this)
    cout<<"\nServer IP is: "<<servAddress<<"\nServer Port is: "<<servPort<<"\nAre these correct?(Y/N)"<<endl;
    cin>>userConfirm;
    bool valid = getchar() == '\n' ? true : false;
    if(!confirm(userConfirm, valid)){exit(1);}
    do //main menu
    {
        cout<<"\nUofI Robotic's Control Menu: "<<endl;
        cout<<"1) CONTROL ROBOT\n2) Change Server's IP Address\n3) Change Server's Port Number\n4) Send Test Message To Server Without Arduino\n5) Send Test Message To Server With Arduino\n6) Quit Program\nEnter a number that is 1-6"<<endl;
     
        userSelection = inputInt();
        switch (userSelection)
        {
            case 1:
                cout<<"haven't implemented"<<endl;
                break;
            case 2:
                cout<<"current address is: "<<servAddress<<"\nEnter new address: ";
                do //keep asking for the address until the user confirms what they have entered
                {
                    cin>>servAddress;
                    cout<<"\nnew address is: "<<servAddress<<endl;
                    cout<<"Is this correct?(Y/N)"<<endl;
                    cin>>userConfirm;
                    valid = getchar() == '\n' ? true : false;
                }
                while(!confirm(userConfirm, valid));
                break;
            case 3:
                cout<<"current port is: "<<servPort<<"\nEnter new Port ";
                do
                {
                    servPort=inputInt();
                    cout<<"\nnew port is: "<<servPort<<endl;
                    cout<<"Is this correct?(Y/N)"<<endl;
                    cin>>userConfirm;
                    valid = getchar() == '\n' ? true : false;
                }
                while(!confirm(userConfirm, valid));
                break;
            case 4:
            {
                cout<<"enter message to send to server"<<endl;
                cin>>tempMessage;
                cout << tempMessage << endl;
                const char *message=tempMessage.c_str();
                try
                {
                    TCPSocket sock(servAddress, servPort); //open socket
                    cout<<"before send"<<endl;
                    sock.send(message, strlen(message)); //send message to server
                    cout<<"after send"<<endl;
                    
                    char echoBuffer[(strlen(message))+1]; //createing a buffer that can capture the message received back from the server
                    int bytesReceived = 0;  // Bytes read on each recv()
                    int totalBytesReceived = 0;  // Total bytes read
                    cout << "Received: ";  // Setup to print the echoed string
                    cout << endl;
                    /*while (totalBytesReceived < strlen(message)+1)
                    {
                        cout<<bytesReceived;
                        // Receive up to the buffer size bytes from the sender
                        if ((bytesReceived = (sock.recv(echoBuffer, strlen(message)+1))) <= 0)
                        {
                            cerr << "Unable to read";
                            exit(1);
                        }
                        totalBytesReceived += bytesReceived;     // Keep tally of total bytes
                        echoBuffer[bytesReceived] = '\0';        // Terminate the string!
                        cout << echoBuffer;                      // Print the echo buffer
                    }*/
                    //cout << endl;
                }
                catch(SocketException &e)
                {
                    cerr << e.what() << endl;
                    exit(1);
                }
                break;
            }
            case 5:
                cout<<"haven't implemented"<<endl;
                break;
            case 6:
                done=false;
                cout<<"Quiting Program!"<<endl;
                break;
                
            default:
                cout<<"Enter a number that is 1-6"<<endl;
                break;
        }
    }
    while(done);
}
/**
 * Input: the user input (should be a 'Y' or an 'N')
 *        a boolean that is true when the user enter a single character and false otherwise
 *
 *  Output: false if the user says no ('N') true otherwisse
 **/
bool confirm(char userConfirm, bool valid)
{
    while((!valid) || (userConfirm!='Y' && userConfirm!='y' && userConfirm!='N' && userConfirm!='n'))
    {
        cout<<"Please input 'Y' or 'N'"<<endl;
        if(!valid){while ( getchar() != '\n' );} //flusing input buffer
        cin>>userConfirm;
        valid = getchar() == '\n' ? true : false;
    }
    if(userConfirm=='N' || userConfirm == 'n')
    {
        cout<<"run again with different arguments"<<endl;
        return false;
    }
    else{return true;} //user confirmed with 'Y'

}
/**
 * function outputs the number the user has inputted
 **/
int inputInt(void)
{
    int input;
    cin>>input;
    while(cin.fail()) //error handling user input
    {
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
        std::cout << "Error: Input is not an integer\nTry again"<<endl;
        std::cin >> input;
    }
    return input;
}
void echoMessage(unsigned int bufferSize)
{
}