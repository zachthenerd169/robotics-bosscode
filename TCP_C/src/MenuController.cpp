/**
 * Filename: MenuController.cpp
 * Created by Stephanie Smith 3/22/2016
 * To compile (on linux or mac terminal): g++ -o MenuController.exe MenuController.cpp
 * To run (on linix or mac terminal): ./MenuController.cpp
 */

#include "headers/MenuController.hpp"

void MenuController::displayMainMenu(void)
{
    std::cout<<"\nUofI Robotic's Control Menu: "<<std::endl;
    std::cout<<"1) CONTROL ROBOT\n2) Change Server's IP Address\n3) Change Server's Port Number\n4) Send Test Message To Server WITHOUT Arduino\n5) Send Test Message To Server WITH Arduino\n6) Quit Program\nEnter a number that is 1-6"<<std::endl;
}
void MenuController::displayRobotMenu(void)
{
    std::cout<<"\nMODE KEY: DESIRED ACTION <user input>\nSTOP ROBOT: <1>\nMOVE STRAIGHT FORWARD: <2 powerLevel>\nMOVE STRAIGHT REVERSE: <3 powerLevel>\nTURN RIGHT: <4 powerLevel>\nTURN LEFT: <5 powerLevel>\nDIGGER DROP: <6>\nRAISE DIGGER: <7>\nDUMP BUCKET: <8>\nLOWER BUCKET: <9>\nREQUEST DATA <10>\n\n"<<std::endl;
    std::cout<<"input 'help' to view mode key\ninput'exit' to quit\notherwise enter the integer that corresponds to the desired command"<<std::endl;
}
void MenuController::displayRequestMenu(void)
{
    std::cout<<"1) Get Image\n2) Get Obstacle Info\n3) Get esitmated distance\n4) Quit\n"<<std::endl;
}
void MenuController::processMainMenu(void)
{
    short userSelection = inputNum(); //get the user input
    bool mainMenuDone=false;
    
    while(!mainMenuDone) //continue until userSelection is 6
    {
        switch (userSelection) //main menu
        {
            case 1:
                displayRobotMenu(); //display the menu first
                processRobotMenu(); //and then begin to process the input
                break;
            case 2:
                changeIPAddress(); //changing the IP address --> IP should be the IP of the server (NUC) you are connecting to
                break;
            case 3:
                changePortNumber(); //changing the port # --> should be the port # the server is listening on
                break;
            case 4:
                sendServerTestMess(); //sending a test message to the server and not the arduino
                break;
            case 5:
                sendArdTestMess(); //senging a test message to the server AND the arduino
                break;
            case 6:
                std::cout<<"GoodBye!"<<std::endl; //quitting program
                mainMenuDone=true;
                break;
            default:
                std::cout<< "error: number must be an integer between 1 and 6\nTry Again"<<std::endl;
                //userSelection wasn't in bounds
        }
        userSelection = inputNum(); //get the user input for every iteration of the while loop
        
    }
}
void MenuController::processRobotMenu(void)
{
}
void MenuController::processRequestMenu(void)
{
}
void MenuController::changeIPAddress(void) //main menu option #2
{
    /*cout<<"current address is: "<<servAddress<<"\nEnter new address: ";
     do //keep asking for the address until the user confirms what they have entered
     {
     cin>>servAddress;
     cout<<"\nnew address is: "<<servAddress<<endl;
     cout<<"Is this correct?(Y/N)"<<endl;
     cin>>userConfirm;
     valid = getchar() == '\n' ? true : false;
     }
     while(!confirm(userConfirm, valid));*/
    
}
void MenuController::changePortNumber(void) //main menu option #3
{
    /*cout<<"current port is: "<<servPort<<"\nEnter new Port ";
     do
     {
     servPort=inputInt();
     cout<<"\nnew port is: "<<servPort<<endl;
     cout<<"Is this correct?(Y/N)"<<endl;
     cin>>userConfirm;
     valid = getchar() == '\n' ? true : false;
     }
     while(!confirm(userConfirm, valid));*/
}
void MenuController::sendArdTestMess(void) //main menu option #4
{
    /*//while ( getchar() != '\n'); //flusing input buffer
     cout<<"enter message that to send to the arduino"<<endl;
     std::getline(std::cin,tempMessage); //getting message
     string arduinoMess="ard-"+tempMessage;
     const char *message=arduinoMess.c_str();
     bool success=sendToServer(servAddress, servPort, message, true);
     if(!success){exit(1);} //exit program if this was unsucessful
     */
    
}
void MenuController::sendServerTestMess(void) //main menu option #5
{
    /*
     //while ( getchar() != '\n'); //flusing input buffer
     cout<<"enter message that to send to the server"<<endl;
     std::getline(std::cin,tempMessage); //getting message
     const char *message=tempMessage.c_str();
     bool success=sendToServer(servAddress, servPort, message, false);
     if(!success){exit(1);} //exit program if this was unsucessful
     break;
     
     */
}
void MenuController::flushInputBuffer(void){while ( getchar() != '\n');} //IO utility function
short MenuController::inputNum(void) //IO utility function
{
    short input;
    std::cin>>input;
    while(std::cin.fail()) //error handling user input
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Error: Input is not an integer\nTry again"<<std::endl;
        std::cin >> input;
    }
    flushInputBuffer();
    return input; //returning the number input
}
bool MenuController::confirm(char userConfirm, bool valid) //IO utility
{
    while((!valid) || (userConfirm!='Y' && userConfirm!='y' && userConfirm!='N' && userConfirm!='n'))
    {
        std::cout<<"Please input 'Y' or 'N'"<<std::endl;
        if(!valid){while ( getchar() != '\n' );} //flusing input buffer
        std::cin>>userConfirm;
        valid = getchar() == '\n' ? true : false;
    }
    if(userConfirm=='N' || userConfirm == 'n')
    {
        std::cout<<"run again with different arguments"<<std::endl;
        return false;
    }
    else{return true;} //user confirmed with 'Y'
    
}
/*bool MenuController::numInBounds(short numInput, short lowerBound, short upperBound)
 {
 if(numInput<=upperBound && numInput>=lowerBound){return true;}
 else
 {
 std::cout<<"error: number must be an integer between "<<lowerBound<<" and "<<upperBound<<"\nTry Again"<<std::endl;
 return false;
 
 }
 }*/


