#include "../UserController.h"
#include <iostream>
#include <xinput.h>

UserController::processInput()
{
	if(Player1->IsConnected())
	{
		m_state = Player1->GetState();

		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (m_xbox_controller.endUp == true) )
		{
			endUp = false;
			powerLevel = powerLevel + 10 < maxPowerLevel ? powerLevel + 10 : maxPowerLevel;
			std::cout << "Power Level: " << powerLevel << std::endl;
			return false;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) {
			m_xbox_controller.endUp = true;
		}

		// Check for d-pad down button (power level decrease)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (m_xbox_controller.endDown == true) )
		{
			m_xbox_controller.endDown = false;
			powerLevel = powerLevel - 10 > 0 ? powerLevel - 10 : 0;
			std::cout << "Power Level: " << powerLevel << std::endl;
			return false;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) {
			m_xbox_controller.endDown = true;
		}

		// Check for A button (forward)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && (m_xbox_controller.endA == true) )
		{
			setInput("2 " + powerLevel);
			//controlRobo(userInput, "moving forward at power level " + powerLevel, servAddress, servPort);
			m_xbox_controller.endA = false;
			std::cout << "Go forward at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			m_xbox_controller.endA = true;
		}

		// Check for B button (turn right)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) && (m_xbox_controller.endB == true))
		{
			setInput("4 " + powerLevel);
			//controlRobo(userInput, "turning right at power level " + powerLevel, servAddress, servPort);
			m_xbox_controller.endB = false;
			std::cout << "Turn right at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
			m_xbox_controller.endB = true;
		}

		// Check for X button (turn left)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) && (m_xbox_controller.endX == true))
		{
			setInput("5 " + powerLevel);
			//controlRobo(userInput, "turning left at power level " + powerLevel, servAddress, servPort);
			m_xbox_controller.endX = false;
			std::cout << "Turn left at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
			m_xbox_controller.endX = true;
		}

		// Check for Y button (backward)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && (m_xbox_controller.endY == true))
		{
			setInput("3 " + powerLevel);
			//controlRobo(userInput, "moving backward at power level " + powerLevel, servAddress, servPort);
			m_xbox_controller.endY = false;
			std::cout << "Go backward at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
			m_xbox_controller.endY = true;
		}

		// Check for RB button (digger drop)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && (m_xbox_controller.endRB == true))
		{
			setInput("6");
			//controlRobo(userInput, "dropping digger", servAddress, servPort);
			m_xbox_controller.endRB = false;
			std::cout << "Dropping Digger" << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
			m_xbox_controller.endRB = true;
		}

		// Check for LB button (digger raise)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) && (m_xbox_controller.endLB == true))
		{
			setInput("7");
			//controlRobo(userInput, "raising digger", servAddress, servPort);
			m_xbox_controller.endLB = false;
			std::cout << "Raising Digger" << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
			m_xbox_controller.endLB = true;
		}
		
		// The following buttons were removed since the robot is built
		// to have the digger and bucket work with the same button press
		// instead these buttons will be for data aquisition (image, ir, and laser range finder)
		
		// Check for Right Thumb button (image)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) && (m_xbox_controller.endRThumb == true))
		{
			// TODO: figure out what the input is for this setInput("8");
			//controlRobo(userInput, "dump bucket", servAddress, servPort);
			m_xbox_controller.endRThumb = false;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) {
			m_xbox_controller.endRThumb = true;
		}

		// Check for Left Thumb button (ir and laser)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) && (m_xbox_controller.endLThumb == true))
		{
			// TODO: figure out what the input is for this setInput("9");
			controlRobo(userInput, "raise bucket", servAddress, servPort);
			m_xbox_controller.endLThumb = false;
			return true;
		}
		
		
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) {
			m_xbox_controller.endLThumb = true;
		}
		

		// Check for start button (stop). I know what you're thinking. Why is start stop? It's close to the right thumb, but still far from the control buttons.
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_START) && (m_xbox_controller.endStart == true))
		{
			setInput("1");
			controlRobo(userInput, "stopping robot", servAddress, servPort);
			m_xbox_controller.endStart = false;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_START)) {
			m_xbox_controller.endStart = true;
		}

		// Check for start button (exit)
		if(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			// TODO: exit somehow
			return false;
		}
		
		// No button pressed during polling return false
		return false;
	}
	else
	{
		// ERROR! PLAYER 1 - XBOX 360 Controller Not Found!
		return false;
	}
}