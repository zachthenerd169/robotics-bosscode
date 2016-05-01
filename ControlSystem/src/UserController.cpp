#include "../UserController.h"
#include <iostream>

bool UserController::changePort(unsigned short new_port)
{
	if (m_socket != nullptr) {
			m_socket->setLocalPort(new_port);
			return true;
		} else
			return false;
}


