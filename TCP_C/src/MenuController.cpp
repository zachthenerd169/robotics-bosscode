/**
 * Filename: MenuController.cpp
 * Created by Stephanie Smith 3/22/2016
 * To compile (on linux or mac terminal): g++ -o MenuController.exe MenuController.cpp
 * To run (on linix or mac terminal): ./MenuController.cpp
 */

#include "headers/MenuController.hpp"

void MenuController::displayMainMenu()
{
    std::cout<<"\nUofI Robotic's Control Menu: "<<std::endl;
    std::cout<<"1) CONTROL ROBOT\n2) Change Server's IP Address\n3) Change Server's Port Number\n4) Send Test Message To Server WITHOUT Arduino\n5) Send Test Message To Server WITH Arduino\n6) Quit Program\nEnter a number that is 1-6"<<std::endl;
}
void MenuController::displayRobotMenu()
{
    std::cout<<"\nMODE KEY: DESIRED ACTION <user input>\nSTOP ROBOT: <1>\nMOVE STRAIGHT FORWARD: <2 powerLevel>\nMOVE STRAIGHT REVERSE: <3 powerLevel>\nTURN RIGHT: <4 powerLevel>\nTURN LEFT: <5 powerLevel>\nDIGGER DROP: <6>\nRAISE DIGGER: <7>\nDUMP BUCKET: <8>\nLOWER BUCKET: <9>\nREQUEST DATA <10>\n\n"<<std::endl;
    std::cout<<"input 'help' to view mode key\ninput'exit' to quit\notherwise enter the integer that corresponds to the desired command"<<std::endl;
}
void MenuController::displayRequestMenu()
{
    std::cout<<"1) Get Image\n2) Get Obstacle Info\n3) Get esitmated distance\n4) Quit\n"<<std::endl;
}
void MenuController::processMainMenu(void)
{
    short userSelection = inputNum(); //get the user input
    while(!numInBounds(userSelection, 1, 6)); //make sure the user inputs and option 1-6
    bool mainMenuDone=false;
    
    while(!mainMenuDone)
    {
        switch (userSelection) //nested menu
        {
            case 1:
                processRobotMenu();
                break;
            case 2:
                changeIPAddress();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                mainMenuDone=true;
                break;
        }
        
    }
}
void MenuController::processRobotMenu(void)
{
}
void MenuController::processRequestMenu(std::string input)
{
}
void MenuController::flushInputBuffer(){while ( getchar() != '\n');}

/*bool MenuController::inputToNum(std::string input) //might get rid of this
{
    istringstream sin(input);
    if (sin) {return true;}
    else {return false;}
    sin >> m_numInput;
    return false;
}*/
            
short MenuController::inputNum(void)
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
bool MenuController::numInBounds(short numInput, short lowerBound, short upperBound)
{
    if(numInput<=upperBound && numInput>=lowerBound){return true;}
    else
    {
        std::cout<<"error: number must be an integer between "<<lowerBound<<" and "<<upperBound<<"\nTry Again"<<std::endl;
        return false;
        
    }
}
void MenuController::changeIPAddress()
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
bool MenuController::confirm(char userConfirm, bool valid)
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



