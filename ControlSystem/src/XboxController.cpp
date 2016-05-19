#include "../XboxController.h" // not sure if this is needed
#include <iostream>
#include <sstream>

std::string XboxController::getMenu()
{
	return "\n---CONTROLS---\nMOTOR POWER LEVEL DOWN: <D-PAD DOWN>\nMOTOR POWER LEVEL UP: <D-PAD UP>\nDIGGER POWER LEVEL DOWN: <D-PAD LEFT>\nDIGGER POWER LEVEL UP: <D-PAD RIGHT>\nSTOP ROBOT: <START>\nMOVE STRAIGHT FORWARD: <A>\nMOVE STRAIGHT REVERSE: <Y>\nTURN RIGHT: <B>\nTURN LEFT: <X>\nDIGGER DROP: <RB>\nRAISE DIGGER: <LB>\nDIGGER ON: <RT>\nDIGGER OFF: <LT>\nREQUEST SENSOR DATA: <LEFT THUMB>\nREQUEST IMAGE: <RIGHT THUMB>\nEXIT: <SELECT>";
}

bool XboxController::processInput()
{
	if(m_player_controller->IsConnected())
	{
		// continuously poll the xbox controller until a command button is pressed
		while(true)
		{
			m_state = m_player_controller->GetState();
			float leftTrigger = (float) m_state.Gamepad.bLeftTrigger / 255;
			float rightTrigger = (float) m_state.Gamepad.bRightTrigger / 255;

			// Check for d-pad up button (power level increase)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (m_xbox_controller.endUp == true) )
			{
				m_xbox_controller.endUp = false;
				int newPowerLevel = getPowerLevel() + 10 < MAX_POWER_LEVEL ? getPowerLevel() + 10 : MAX_POWER_LEVEL;
				setPowerLevel(newPowerLevel);
				std::cout << "Motor Power Level: " << getPowerLevel() << std::endl;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) {
				m_xbox_controller.endUp = true;
			}

			// Check for d-pad down button (power level decrease)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (m_xbox_controller.endDown == true) )
			{
				m_xbox_controller.endDown = false;
				int newPowerLevel = getPowerLevel() - 10 > 0 ? getPowerLevel() - 10 : 0;
				setPowerLevel(newPowerLevel);
				std::cout << "Motor Power Level: " << getPowerLevel() << std::endl;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) {
				m_xbox_controller.endDown = true;
			}

			// Check for d-pad right button (digger power level increase)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && (m_xbox_controller.endRight == true) )
			{
				m_xbox_controller.endRight = false;
				int newPowerLevel = getPowerLevelDigger() + 10 < MAX_POWER_LEVEL_DIGGER ? getPowerLevelDigger() + 10 : MAX_POWER_LEVEL_DIGGER;
				setPowerLevelDigger(newPowerLevel);
				std::cout << "Digger Power Level: " << getPowerLevelDigger() << std::endl;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
				m_xbox_controller.endRight = true;
			}

			// Check for d-pad left button (digger power level decrease)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && (m_xbox_controller.endLeft == true) )
			{
				m_xbox_controller.endLeft = false;
				int newPowerLevel = getPowerLevelDigger() - 10 > 0 ? getPowerLevelDigger() - 10 : 0;
				setPowerLevelDigger(newPowerLevel);
				std::cout << "Digger Power Level: " << getPowerLevelDigger() << std::endl;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
				m_xbox_controller.endLeft = true;
			}

			// Check for A button (forward)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && (m_xbox_controller.endA == true) )
			{
				setInput("[M2" + int_to_string(getPowerLevel()) + "]");
				m_xbox_controller.endA = false;
				std::cout << "Go forward at power level: " << getPowerLevel() << std::endl;
				return true;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
				m_xbox_controller.endA = true;
			}

			// Check for B button (turn right)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) && (m_xbox_controller.endB == true))
			{
				setInput("[M4" + int_to_string(getPowerLevel()) + "]");
				m_xbox_controller.endB = false;
				std::cout << "Turn right at power level: " << getPowerLevel() << std::endl;
				return true;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
				m_xbox_controller.endB = true;
			}

			// Check for X button (turn left)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) && (m_xbox_controller.endX == true))
			{
				setInput("[M5" + int_to_string(getPowerLevel()) + "]");
				m_xbox_controller.endX = false;
				std::cout << "Turn left at power level: " << getPowerLevel() << std::endl;
				return true;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
				m_xbox_controller.endX = true;
			}

			// Check for Y button (backward)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && (m_xbox_controller.endY == true))
			{
				setInput("[M3" + int_to_string(getPowerLevel()) + "]");
				m_xbox_controller.endY = false;
				std::cout << "Go backward at power level: " << getPowerLevel() << std::endl;
				return true;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
				m_xbox_controller.endY = true;
			}

			// Check for RB button (digger drop)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && (m_xbox_controller.endRB == true))
			{
				setInput("[M6]");
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
				setInput("[M7]");
				m_xbox_controller.endLB = false;
				std::cout << "Raising Digger" << std::endl;
				return true;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) {
				m_xbox_controller.endLB = true;
			}

			// Check for Right trigger (digger on)
			if((rightTrigger > 0.1) && (m_xbox_controller.endRT == true))
			{
				setInput("[M8" + int_to_string(getPowerLevelDigger()) + "]");
				m_xbox_controller.endRT = false;
				std::cout << "Digger On" << std::endl;
				return true;
			}
			else if(!(rightTrigger > 0.1)) {
				m_xbox_controller.endRT = true;
			}

			// Check for Left trigger (digger off)
			if((leftTrigger > 0.1) && (m_xbox_controller.endLT == true))
			{
				setInput("[M9]");
				m_xbox_controller.endLT = false;
				std::cout << "Digger Off" << std::endl;
				return true;
			}
			else if(!(leftTrigger > 0.1)) {
				m_xbox_controller.endLT = true;
			}

			// The following buttons were removed since the robot is built
			// to have the digger and bucket work with the same button press
			// instead these buttons will be for data aquisition (image, ir, and laser range finder)

			// Check for Right Thumb button (image)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) && (m_xbox_controller.endRThumb == true))
			{
				setInput("[I]");
				m_xbox_controller.endRThumb = false;
				return true;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) {
				m_xbox_controller.endRThumb = true;
			}

			// Check for Left Thumb button (ir and laser)
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) && (m_xbox_controller.endLThumb == true))
			{
				setInput("[S]");
				m_xbox_controller.endLThumb = false;
				return true;
			}


			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) {
				m_xbox_controller.endLThumb = true;
			}


			// Check for start button (stop). I know what you're thinking. Why is start stop? It's close to the right thumb, but still far from the control buttons.
			if((m_state.Gamepad.wButtons & XINPUT_GAMEPAD_START) && (m_xbox_controller.endStart == true))
			{
				setInput("[M1]");
				m_xbox_controller.endStart = false;
				return true;
			}
			else if(!(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_START)) {
				m_xbox_controller.endStart = true;
			}

			// Check for select button (exit)
			if(m_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				std::cout << "Exiting Client Program";
				return false;
			}

		}
	}
	else
	{
		// ERROR! PLAYER 1 - XBOX 360 Controller Not Found!
		std::cout << "Controller not found, exiting Client Program";
		return false;
	}
}


std::string int_to_string(int value)
{
    std::ostringstream os;
    os << value;
    std::string temp_string = os.str();
    if(temp_string.length() == 1)
    {
        temp_string = "00" + temp_string;
    }
    else if(temp_string.length() == 2)
    {
        temp_string = "0" + temp_string;
    }
    return temp_string;
}
