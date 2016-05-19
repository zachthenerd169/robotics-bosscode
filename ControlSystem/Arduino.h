#ifndef ARDUINO_H_
#define ARDUINO_H_
#include <iostream>
#include "lib/arduino-serial-lib.h"

class Arduino{
	
	public:
		Arduino(){fd=-1;}
		Arduino operator()(const char* port, int baud_rate=9600)
		{
			Arduino a(port, baud_rate);
			return a;
		}
		/**
		 *
		 */
		Arduino(const char* port, int baud_rate=9600)
		{
			fd=-1;
			fd = serialport_init(port, baud_rate); //opening port
    		(fd == -1) ? throw std::invalid_argument("Couldn't open port" + std::string(port)) : std::cout<< "opened port " << port << std::endl;
    		serialport_flush(fd);
    	}
		/**
		 * Description: writes the string to the arduino
		 * Input: the message to be written
		 */
		void write(std::string message);

	private:
		int fd;
};

#endif
