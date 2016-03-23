/**
 * Filename: MenuController.hpp
 * Created by Stephanie Smith 3/22/2016
 * To compile MenuController.cpp (on linux or mac terminal): g++ -o MenuController.exe MenuController.cpp
 * To run MenuController.cpp (on linix or mac terminal): ./MenuController.cpp
 *
 * Class Description:
 */

#include <string> //For user inputs
#include <iostream> //For cerr and cout

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
        void processRobotMenu(std::string input);
        void processRequestMenu(std::string input);
    
        /*getters*/
        short getNumInput(void){return m_numInput;}
        std::string getStrInput(void){return m_strInput;}
    
    private:
        short m_numInput;
        std::string m_strInput;
        /*setters*/
        void setNumInput(short numInput){m_numInput=numInput;}
        void setStrInput(std::string strInput){m_strInput=strInput;}
    
        void flushInputBuffer(void);
        //bool inputToNum(std::string input);
        short inputNum(void);
        bool numInBounds(short numInput, short lowerBound, short upperBound);
};


/**
 * Test Description:
 */
#if DEBUG
    int main(void)
    {
        std::cout<<"menu test"<<std::endl;
    }
#endif