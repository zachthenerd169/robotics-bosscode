#include "../UserController.h"
#include <iostream>

/*UserController::changePort(unsigned short new_port)

{
	if(m_socket!=nullptr)
	{
		m_socket->setLocalPort(new_port);
		return true;
	}
	else return false;
}*/

UserController::processInput(std::string &processed_input)
{
	if(Player1->IsConnected())
	{
		m_state = Player1->GetState();

		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (endUp == true) )
		{
			endUp = false;
			powerLevel = powerLevel + 10 < maxPowerLevel ? powerLevel + 10 : maxPowerLevel;
			std::cout << "Power Level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) {
			endUp = true;
		}

		// Check for d-pad down button (power level decrease)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (endDown == true) )
		{
			endDown = false;
			powerLevel = powerLevel - 10 > 0 ? powerLevel - 10 : 0;
			std::cout << "Power Level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) {
			endDown = true;
		}

		// Check for A button (forward)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && (endA == true) )
		{
			userInput = "2 " + powerLevel;
			controlRobo(userInput, "moving forward at power level " + powerLevel, servAddress, servPort);
			endA = false;
			std::cout << "Go forward at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			endA = true;
		}

		// Check for B button (turn right)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) && (endB == true))
		{
			userInput = "4 " + powerLevel
			controlRobo(userInput, "turning right at power level " + powerLevel, servAddress, servPort);
			endB = false;
			std::cout << "Turn right at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
			endB = true;
		}

		// Check for X button (turn left)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) && (endX == true))
		{
			userInput = "5 " + powerLevel;
			controlRobo(userInput, "turning left at power level " + powerLevel, servAddress, servPort);
			endX = false;
			std::cout << "Turn left at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
			endX = true;
		}

		// Check for Y button (backward)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && (endY == true))
		{
			userInput = "3 " + powerLevel;
			controlRobo(userInput, "moving backward at power level " + powerLevel, servAddress, servPort);
			endY = false;
			std::cout << "Go backward at power level: " << powerLevel << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
			endY = true;
		}

		// Check for RB button (digger drop)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && (endRB == true))
		{
			userInput = "6";
			controlRobo(userInput, "dropping digger", servAddress, servPort);
			endRB = false;
			std::cout << "Dropping Digger" << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
			endRB = true;
		}

		// Check for LB button (digger raise)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) && (endLB == true))
		{
			userInput = "7";
			controlRobo(userInput, "raising digger", servAddress, servPort);
			endLB = false;
			std::cout << "Raising Digger" << std::endl;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
			endLB = true;
		}

		// Check for Right Thumb button (dump bucket)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) && (endRThumb == true))
		{
			userInput = "8";
			controlRobo(userInput, "dump bucket", servAddress, servPort);
			endRThumb = false;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) {
			endRThumb = true;
		}

		// Check for Left Thumb button (raise bucket)
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) && (endLThumb == true))
		{
			userInput = "9";
			controlRobo(userInput, "raise bucket", servAddress, servPort);
			endLThumb = false;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) {
			endLThumb = true;
		}

		// Check for start button (stop). I know what you're thinking. Why is start stop? It's close to the right thumb, but still far from the control buttons.
		if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_START) && (endStart == true))
		{
			userInput = "1";
			controlRobo(userInput, "stopping robot", servAddress, servPort);
			endStart = false;
			return true;
		}
		else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_START)) {
			endStart = true;
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

// TODO: move this polling loop to a more appropriate location
/*
int main(void)
{
	while(!done)
	{
		if(processInput(&m_input))
		{
			sendData(m_input);
		}
		
	}
	return 0;
}
*/
