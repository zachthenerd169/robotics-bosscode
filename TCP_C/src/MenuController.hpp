/**
 * Filename: MenuController.hpp
 * Created by Stephanie Smith 3/22/2016
 * To compile MenuController.cpp (on linux or mac terminal): g++ -o MenuController.exe MenuController.cpp
 * To run MenuController.cpp (on linix or mac terminal): ./MenuController.cpp
 *
 * Class Description:
 */

#include <string>   //For user inputs
#include <iostream> //For cerr and cout
#include <sstream>  // for split(string)
#include <vector>   // also for split(string)
#include <cstdlib>  // For atoi()
#include "Client.hpp"

#define DEBUG 1 //1 when debugging code, make 0 when you are no longer testing this class

class MenuController
{
    public:
    
        /*For the command-line interface there are three different types of
         menus to be dispayed*/
    
        void displayMainMenu(void); //debug commands, change IP/port, control robot, control via Xbox Controller
        void displayRobotMenu(void); //to send commands to the robot (controlling motors)
        void displayRequestMenu(void); //to request info from the robot
    
        void processMainMenu(void);
        void processRobotMenu(void);
        void processRequestMenu(void);
    
        /*getters*/
        short getNumInput(void){return m_numInput;}
        std::string getStrInput(void){return m_strInput;}
    
    private:
    
        /*fields*/
        //Client client("127.0.0.1", 1024); //hard coding ports for now
    
        /*setters*/
        void setNumInput(short numInput){m_numInput=numInput;}
        void setStrInput(std::string strInput){m_strInput=strInput;}
    
        /*menu utility functions*/
        void changeIPAddress();
        void changePortNumber(void);
        void sendArdTestMess(void);
        void sendServerTestMess(void);
    
        bool controlRobot(std::string userInput, std::string message, std::string servAddress, unsigned short servPort);
    
        /*IO utility functions*/
        short inputNum(void);
        bool confirm(char userConfirm, bool valid);
        void flushInputBuffer(void);
        bool checkUserInput(std::vector<std::string> input, short numArguments);
    
        /*utility string functions*/
        std::vector<std::string> splitString(std::string str);
};


/**
 * Test Description:
 */
#if DEBUG
    int main(void)
    {
        MenuController mc; //creating menu object
        mc.displayMainMenu();
        mc.processMainMenu();
        return 0;
    }
#endif