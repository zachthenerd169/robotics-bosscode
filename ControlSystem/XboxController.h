/*
 * XboxController.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 * Class Description: XboxController allows the user to control the robot with and xbox controller,
 * 					  If using an xbox controller, the client code must be loaded on a windows computer
 *
 * Control Key:
 */

#include "UserController.h"
#include "lib/CXBOXController.h" // for xbox controller
#include "util/Modes.h"


#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_

/**
 * Description: Helper function for converting integer to string (std::to_string doesn't work on MINGW)
 * Inputs: the integer to convert to a string
 * Outputs: the converted string
 */
 std::string int_to_string(int value);

class XboxController : public UserController
{
	public:
		/**
		 * Description: creates a TCPSocket objects, xbox controller is initialized so the nothing is pressed
		 * Inputs: the IP Address of the NUC (the computer on the robot)
		 * 		   the port number the NUC is listening on
		 */
		XboxController(std::string address, unsigned short port):
				UserController(address, port),m_xbox_controller(){};
		/**
		 * Description: default constructor
		 * Input: none
		 */
		XboxController():UserController(),m_xbox_controller(){};

		/**
		 * Description: initializes the controller
		 * Input: none
		 */
		void initializeController(){m_player_controller = new CXBOXController(1);}

		/**
		 * Description: Checks if the user has pressed a button that hasn't been pressed.
		 * Inputs: string that stores the processed input that is to be sent to the robot
		 * Outputs: returns true if command was successfully processed, returns false
		 * 			otherwise. Note, power change button presses are not commands.
		 */
		bool processInput();
		/**
		 * Description: setter for power level
		 * Input: new power level
		 */
		void setPowerLevel(int powerLevel){m_power_level=powerLevel;}
		/**
		 * Description: getter for power level
		 * Output: the current power level
		 */
		int getPowerLevel(){return m_power_level;}
		/**
		 * Description: setter for power level
		 * Input: new power level
		 */
		void setPowerLevelDigger(int powerLevel){m_power_level_digger=powerLevel;}
		/**
		 * Description: getter for power level
		 * Output: the current power level
		 */
		int getPowerLevelDigger(){return m_power_level_digger;}
		/**
		 * Description: gets the menu which displays controls
		 * Output: the text menu
		 */
		std::string getMenu();
		/**
		 * Description: Destructor
		 */
		 ~XboxController(){}


		/**
		* constant that specifies the absolute largest power level
		*/
		static const int MAX_POWER_LEVEL = 120;

		/**
		* constant that specifies the absolute largest power level for the digger
		*/
		static const int MAX_POWER_LEVEL_DIGGER = 120;
	private:
		/**
		 * holds the button press state of the xbox controller
		 * if a member value is false the button is being held
		 * if a member value is true the button is released
		 */
		struct ButtonState
		{
			bool endA;
			bool endB;
			bool endX;
			bool endY;
			bool endUp;
			bool endDown;
			bool endStart;
			bool endRB;
			bool endLB;
			bool endRThumb;
			bool endLThumb;
			bool endLT;
			bool endRT;
			bool endLeft;
			bool endRight;
		}m_xbox_controller;

		/**
		* tells whether the last digger action was a lower
		*/
		bool m_lowered = false;

		/**
		* tells whether the last digger action was a raise
		*/
		bool m_raised = false;

		/**
		* holds the current power level as adjusted
		* by the controller
		*/
		int m_power_level = 0;

		/**
		* holds the current power level for the digger as adjusted
		* by the controller
		*/
		int m_power_level_digger = 0;

		/**
		* holds the current state of the xbox controller
		*/
		XINPUT_STATE m_state;

		/**
		* points to the controller being used
		*/
		CXBOXController* m_player_controller;


};
#endif /* XBOXCONTROLLER_H_ */
