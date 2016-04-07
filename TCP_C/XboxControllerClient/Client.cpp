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
#include <sstream>            // for split(string)
#include <vector>             // also for split(string)



bool confirm(char userConfirm, bool valid); //prototypes
int inputInt(void);
void echoMessage(TCPSocket *sock, unsigned int bufferSize);
bool sendToServer(string servAddress, unsigned short servPort, const char* message, bool arduino);
vector<string> splitString(string str);
bool checkUserInput(vector<string> input, int numArguments);
bool controlRobo(string userInput, string message, string servAddress, int servPort);



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
        switch (userSelection) //nested menu
        {
            case 1:
            {
                // These booleans determine whether a button is being held down
                bool endA = true;
                bool endB = true;
                bool endX = true;
                bool endY = true;
                bool endUp = true;
                bool endDown = true;
                bool endStart = true;
                bool endRB = true;
                bool endLB = true;

                // The current set power level and max power level
                int powerLevel = 0;
                final int maxPowerLevel = 50;

                // Set the deadzones for the analog (not being used currently)
                float deadzoneX = 0.05f;
                float deadzoneY = 0.02f;

                Player1 = new CXBOXController(1);

                std::cout << "Instructions:\n";
                std::cout << "[A] Go forward\n";
                std::cout << "[B] Rotate Right\n";
                std::cout << "[X] Rotate Left\n";
                std::cout << "[Y] Go backward\n";
                std::cout << "[START] Stop\n";
                std::cout << "[BACK] Exit\n";

                bool robotDone = false;

                while(!robotDone)
                {
                    if(Player1->IsConnected())
                    {
                        XINPUT_STATE state = Player1->GetState();

                        // The follow commented block is for reading analog input
                        // and adjusting the deadzone. We currently do not need this
                        /*
                        float LX = state.Gamepad.sThumbRX;
                        float LY = state.Gamepad.sThumbRY;

                        //determine how far the controller is pushed
                        float magnitude = sqrt(LX*LX + LY*LY);

                        //determine the direction the controller is pushed
                        float normalizedLX = LX / magnitude;
                        float normalizedLY = LY / magnitude;

                        float normalizedMagnitude = 0;

                        //check if the controller is outside a circular dead zone
                        if (magnitude > INPUT_DEADZONE)
                        {
                          //clip the magnitude at its expected maximum value
                          if (magnitude > 32767) magnitude = 32767;

                          //adjust magnitude relative to the end of the dead zone
                          magnitude -= INPUT_DEADZONE;

                          //optionally normalize the magnitude with respect to its expected range
                          //giving a magnitude value of 0.0 to 1.0
                          normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);
                        }
                        else //if the controller is in the deadzone zero out the magnitude
                        {
                            magnitude = 0.0;
                            normalizedMagnitude = 0.0;
                        }

                        normalizedMagnitude = pow(normalizedMagnitude,3);
                        */

                        // Check for d-pad up button (power level increase)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (endUp == true) )
                        {
                            endUp = false;
                            powerLevel = powerLevel + 10 < maxPowerLevel ? powerLevel + 10 : maxPowerLevel;
                            std::cout << "Power Level: " << powerLevel << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) {
                            endUp = true;
                        }

                        // Check for d-pad down button (power level decrease)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (endDown == true) )
                        {
                            endDown = false;
                            powerLevel = powerLevel - 10 > 0 ? powerLevel - 10 : 0;
                            std::cout << "Power Level: " << powerLevel << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) {
                            endDown = true;
                        }

                        // Check for A button (forward)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && (endA == true) )
                        {
                            userInput = "2 " + powerLevel;
                            controlRobo(userInput, "moving forward at power level " + powerLevel, servAddress, servPort);
                            endA = false;
                            //Player1->Vibrate(65535, 0);
                            std::cout << "Go forward at power level: " << powerLevel << std::endl;


                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
                            endA = true;
                        }

                        // Check for B button (turn right)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) && (endB == true))
                        {
                            userInput = "4 " + powerLevel
                            controlRobo(userInput, "turning right at power level " + powerLevel, servAddress, servPort);
                            endB = false;
                            //Player1->Vibrate(0, 65535);
                            std::cout << "Turn right at power level: " << powerLevel << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
                            endB = true;
                        }

                        // Check for X button (turn left)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) && (endX == true))
                        {
                            userInput = "5 " + powerLevel;
                            controlRobo(userInput, "turning left at power level " + powerLevel, servAddress, servPort);
                            endX = false;
                            //Player1->Vibrate(65535, 65535);
                            std::cout << "Turn left at power level: " << powerLevel << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
                            endX = true;
                        }

                        // Check for Y button (backward)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && (endY == true))
                        {
                            userInput = "3 " + powerLevel;
                            controlRobo(userInput, "moving backward at power level " + powerLevel, servAddress, servPort);
                            endY = false;
                            //Player1->Vibrate();
                            std::cout << "Go backward at power level: " << powerLevel << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
                            endY = true;
                        }

                        // Check for RB button (digger drop)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && (endRB == true))
                        {
                            userInput = "6";
                            controlRobo(userInput, "dropping digger", servAddress, servPort);
                            endRB = false;
                            //Player1->Vibrate();
                            std::cout << "Dropping Digger" << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
                            endRB = true;
                        }

                        // Check for LB button (digger raise)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) && (endLB == true))
                        {
                            userInput = "7";
                            controlRobo(userInput, "raising digger", servAddress, servPort);
                            endLB = false;
                            //Player1->Vibrate();
                            std::cout << "Raising Digger" << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
                            endLB = true;
                        }

                        // Check for Right Thumb button (dump bucket)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) && (endRThumb == true))
                        {
                            userInput = "8";
                            controlRobo(userInput, "dump bucket", servAddress, servPort);
                            endRThumb = false;
                            //Player1->Vibrate();
                            std::cout << "Dumping Bucket" << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) {
                            endRThumb = true;
                        }

                        // Check for Left Thumb button (raise bucket)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) && (endLThumb == true))
                        {
                            userInput = "9";
                            controlRobo(userInput, "raise bucket", servAddress, servPort);
                            endLThumb = false;
                            //Player1->Vibrate();
                            std::cout << "Raising Bucket" << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) {
                            endLThumb = true;
                        }

                        // Check for start button (stop)
                        if((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) && (endStart == true))
                        {
                            userInput = "1";
                            controlRobo(userInput, "stopping robot", servAddress, servPort);
                            endStart = false;
                            std::cout << "Robot Stopped" << std::endl;
                        }
                        else if(!(state.Gamepad.wButtons & XINPUT_GAMEPAD_START)) {
                            endStart = true;
                        }

                        // Check for start button (exit)
                        if(state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
                        {
                            std::cout << "Exited" << std::endl;
                            robotDone = true;
                        }

                    }
                    else
                    {
                        std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
                        std::cout << "Press Any Key To Exit.";
                        std::cin.get();
                        break;
                    }
                }
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

    char echoBuffer[bufferSize+1]; //createing a buffer that can capture the message received back from the server
    int bytesReceived = 0;  // Bytes read on each recv()
    int totalBytesReceived = 0;  // Total bytes read
    while (totalBytesReceived < bufferSize)
    {
        cout << "Echoed: ";  // Setup to print the echoed string
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
/**
 * description: splits the string at the ' '
 * input: a single string
 * output: a vector of strings --> where each element is a word
 **/
vector<string> splitString(string str) //this may be used on the server side too
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
/**
 * For the control robot menu item, this function checks if the user input is reasonble (ie it has the correct format and a feasible power level
 * input: a vector (the user's input)
 *        the expected size of the vector (it should either be 1 or 2)
 * output: true if the input is reasonable; false otherwise
 **/
bool checkUserInput(vector<string> input, int numArguments)
{
    if(input.size()!=numArguments){return false;}
    else if(input.size()==2) //if the power level was specified
    {
        int pow1=atoi(input[1].c_str()); //checking if the power levels are acceptable
        if(pow1<-127 || pow1>127)
        {
            cout<<"incorrect power input: power level ranges from -127 to 127"<<endl;
            return false; //power needs to be in the -127-127
        }
        else{return true;}
    }
    return true; //if it's the correct # of arguments the input is fine
}
/**
 *  Function sends message to the server (that will then send a message to the arduino) and prints status message
 *  inputs: string userinput (robot command to send to server)
 *          string mess (status message to print out)
 *          string servAddress (the IP address of the server)
 *          int servPort (the port the server is listening on)
 *  outputs: true if the message sends successfully; false otherwise
 **/
bool controlRobo(string userInput, string message, string servAddress, int servPort)
{
    userInput="ard-"+userInput; //adding the to send to arduino
    bool success=sendToServer(servAddress, servPort, userInput.c_str(), true); //make true later -->true once you have an arduino
    cout<<message<<endl; //print status message
    return !success ? false : true;
}
