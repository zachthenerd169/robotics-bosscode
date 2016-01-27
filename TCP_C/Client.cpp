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
#include <sstream>
#include <vector>


bool confirm(char userConfirm, bool valid); //prototypes
int inputInt(void);
void echoMessage(TCPSocket *sock, unsigned int bufferSize);
bool sendToServer(string servAddress, unsigned short servPort, const char* message, bool arduino);
vector<string> splitString(string str);
bool checkUserInput(vector<string> input, int numArguments);



int main (int argc, char *argv[])
{
    //cout<<"size of boolean "<<sizeof(test)<<endl;
    /*bool bits[] = {0, 1, 0, 0, 0, 0, 0, 1};
    char c = 0;
    for(int i = 0; i < 8; i++)
        c += (bits[i] >> i); // 0 or 1 times 2 to the ith power
    cout << c << endl; // should print out A
    cin.get();
    return 0;*/


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
        switch (userSelection) //nested menu
        {
            case 1:
            {
                string userInput;
                bool viewKey=true;
                int powerLevel=0;
                int mode=-1;
                bool success=false;
                bool robotDone=false; //flag to control robot submenu
                do{
                    //representing in the least amount of bits:
                    //3 bits for mode; 5 bits for each power if the power is incremented by ten
                    //13 bits total woo
                    //can send two bits or can send boolean array
                    if(viewKey)
                    {
                        cout<<"\nMODE KEY: DESIRED ACTION <user input>\nSTOP ROBOT: <0>\nMOVE STRAIGHT FORWARD: <1 powerLevel>\nMOVE STRAIGHT REVERSE: <2 powerLevel>\nTURN RIGHT: <3 powerLevel>\nTURN LEFT: <4 powerLevel>\nDIGGER DROP: <5>\nRAISE DIGGER: <6>\nDUMP BUCKET: <7>\nLOWER BUCKET: <8>\n\n"<<endl;
                        /*cout<<"COMMAND KEY:\n0) stop\n1) forward\n2) reverse\n3) right\n4) left\n5) digger drop\n6) raise digger\n7) dump bucket\n8) lower bucket\n9) change drive power level\n10) change digger power level\n"<<endl;*/
                    }
                    viewKey=false; //only dispay this when the user wants to
                    cout<<"input 'help' to view mode key\ninput'exit' to quit\notherwise enter the integer that corresponds to the desired command"<<endl;
                    while ( getchar() != '\n'); //flusing input buffer
                    std::getline(std::cin, userInput);
                    if(userInput.compare("help")==0){viewKey=true;}
                    else if(userInput.compare("exit")==0) {robotDone=true;}
                    else
                    {
                        cout<<"size of input: "<<sizeof(userInput.c_str())<<endl;
                        vector<string> inputs= splitString(userInput);
                        mode=atoi(inputs[0].c_str());
                        if(mode==0)//stop robot
                        {
                            success=sendToServer(servAddress, servPort, userInput.c_str(), false); //will be 'true' later
                            if(!success){exit(1);} //exit program if this was unsucessful
                            cout<<"stopping robot"<<endl;
                        }
                        else if(mode>0 && mode<5)//turn right;left;straight;reverse //ask for power levels here
                        {
                            
                            switch (mode)
                            {
                                case 1:
                                    
                                    powerLevel=atoi(inputs[1].c_str());
                                    //controlRobo(userInput, string "moving forward at power level"+powerLevel);
                                    break;
                                case 2:
                                    powerLevel=atoi(inputs[1].c_str());
                                    success=sendToServer(servAddress, servPort, userInput.c_str(), false);
                                    cout<<"moving backwards at power level "<<powerLevel<<endl;
                                    break;
                                case 3:
                                    powerLevel=atoi(inputs[1].c_str());
                                    success=sendToServer(servAddress, servPort, userInput.c_str(), false);
                                    cout<<"turning right at power level "<<powerLevel<<endl;
                                    break;
                                case 4:
                                    powerLevel=atoi(inputs[1].c_str());
                                    success=sendToServer(servAddress, servPort, userInput.c_str(), false);
                                    cout<<"turning left at power level "<<powerLevel<<endl;
                                default:
                                    break;
                            }
                        }
                        else if(mode<11 && mode>4)//digger drop; digger raise; bucket drop; bucket raise
                        {
                            bool success=sendToServer(servAddress, servPort, userInput.c_str(), false); //will be 'true' later
                            if(!success){exit(1);} //exit program if this was unsucessful
                            switch (mode)
                            {
                                case 5:
                                    cout<<"dropping digger"<<endl;
                                    break;
                                case 6:
                                    cout<<"raising digger"<<endl;
                                    break;
                                case 7:
                                    cout<<"dumping bucket"<<endl;
                                    break;
                                case 8:
                                    cout<<"raising bucket"<<endl;
                                    break;
                                case 9:
                                    cout<<"raising bucket"<<endl;
                                    break;
                                case 10:
                                    cout<<"raising bucket"<<endl;
                                    break;
                                default:
                                    break;
                            }
                        }
                        else //didn't input the right number
                        {
                            cout<<"input an integer 0-10 and powerlevel if required"<<endl;
                        }
                    }
                }
                while(!robotDone);//stay in this menu while the user does not input "exit"
                break;
            }
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
               
                while ( getchar() != '\n'); //flusing input buffer
                cout<<"enter message that to send to the server"<<endl;
                std::getline(std::cin,tempMessage); //getting message
                const char *message=tempMessage.c_str();
                bool success=sendToServer(servAddress, servPort, message, false);
                if(!success){exit(1);} //exit program if this was unsucessful
                break;
            }
            case 5:
            {
                while ( getchar() != '\n'); //flusing input buffer
                cout<<"enter message that to send to the arduino"<<endl;
                std::getline(std::cin,tempMessage); //getting message
                string arduinoMess="ard-"+tempMessage;
                const char *message=arduinoMess.c_str();
                bool success=sendToServer(servAddress, servPort, message, true);
                if(!success){exit(1);} //exit program if this was unsucessful
                break;
            }
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
 * Output: The number the user has inputted
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
/**
 *  Input: the server address and the server port number
 **/
bool sendToServer(string servAddress, unsigned short servPort, const char* message, bool arduino)
{
    int bufferSize= arduino ? (strlen(message) + strlen("Arduino received: "))-3 : strlen(message); //I think I need to subtract 3 b/c I'm double counting spaces
    cout <<"buffer size: " <<bufferSize << endl;
    try
    {
        TCPSocket sock(servAddress, servPort); //open socket
        sock.send(message, strlen(message)); //send message to server
        echoMessage(&sock, bufferSize);
        return true;
    }
    catch(SocketException &e)
    {
        cerr << e.what() << endl;
        return false;
    }
}
/**
 *  Function prints out the message received from server
 *  Input: TCPSocket and the size of the message that is sent to the server
 **/
void echoMessage(TCPSocket *sock, unsigned int bufferSize)
{
    cout << "Echoed: ";  // Setup to print the echoed string
    char echoBuffer[bufferSize+1]; //createing a buffer that can capture the message received back from the server
    int bytesReceived = 0;  // Bytes read on each recv()
    int totalBytesReceived = 0;  // Total bytes read
    while (totalBytesReceived < bufferSize)
    {
        // Receive up to the buffer size bytes from the sender
        if ((bytesReceived = (sock->recv(echoBuffer, bufferSize+1))) <= 0)
        {
            cerr << "Unable to read";
            exit(1);
        }
        totalBytesReceived += bytesReceived;     // Keep tally of total bytes
        echoBuffer[bytesReceived] = '\0';        // Terminate the string!
        cout <<echoBuffer;
    }
    cout << endl;

}
vector<string> splitString(string str)
{
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words
    
    while (ss >> buf)
        tokens.push_back(buf);
    
    for(int i=0; i<tokens.size(); i++)
    {
        cout<<tokens[i]<<endl;
    }
    return tokens;
}
bool checkUserInput(vector<string> input, int numArguments)
{
    if(input.size()==numArguments){return false;}
    else if(input.size()==2) //if the power level was specified
    {
        int pow1=atoi(input[0].c_str()); //checking if the power levels are acceptable
        if(pow1<=127 || pow1>=127)
        {
            return false; //power needs to be in the -127-127
        }
        else{return true;}
    }
    return true; //if it's the correct # of arguments the input is fine
}
/*
void controlRobo(string userInput, string message)
{
    bool success=sendToServer(servAddress, servPort, userInput.c_str(), true);
    if(!success){exit(1);}
    cout<<message<<endl;
}*/