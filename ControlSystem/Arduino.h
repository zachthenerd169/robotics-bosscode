#ifndef ARDUINO_H_
#define ARDUINO_H_
#include <iostream>
#include "lib/arduino-serial-lib.h"

class Arduino{
	
	public:
		/**
		 *
		 */
		Arduino()
		{
			fd_motors=-1;
			fd_motors = serialport_init(MOTOR_PORT, BAUD_RATE); //opening port
    		(fd_motors == -1) ? std::cout<< "couldn't open port for arduino! :(" << std::endl : std::cout<< "opened port " << MOTOR_PORT << std::endl;
    		serialport_flush(fd_motors);
    	}
		/**
		 * Description: writes the string to the arduino
		 * Input: the message to be written
		 */
		void writeToMotors(std::string message);

	private:
		int fd_motors;
		const char* MOTOR_PORT="/dev/cu.usbmodem1421"; //steph's port
		const int BAUD_RATE=57600;
};

#endif
