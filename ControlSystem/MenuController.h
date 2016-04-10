/*
 * MenuController.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef MENUCONTROLLER_H_
#define MENUCONTROLLER_H_

class MenuController : UserController
{
	public:
		std::string getMainMenu();
		std::string getRobotMenu(); //maybe we don't want 3 different menus?
		std::string getRequestMenu();
		/**
		 * returns true if the input was successfully processed
		 * std::string will store the input that is to be sent over
		 * the network
		 */
		bool processInput(std::string &input);
	private:
		std::string m_input;

};



#endif /* MENUCONTROLLER_H_ */
