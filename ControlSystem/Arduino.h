#ifndef ARDUINO_H_
#define ARDUINO_H_

class Arduino{
	
	public:
		/**
		 *
		 */
		Arduino()
		{
			fd_motors=-1;
			fd_motors = serialport_init(port, BAUDRATE); //opening port
    		(fd_motors == -1) ? std::cout<< "couldn't open port for arduino! :(" << std::endl : std::cout<< "opened port " << port << std::endl;
    		serialport_flush(fd_motors);
    	}
		/**
		 * Description: writes the string to the arduino
		 * Input: the message to be written
		 */
		std::string writeToMotors(std::string message);

	private:
		int fd_motors;
		const char* MOTOR_PORT="/dev/cu.usbmodem1411"; //steph's port
		const int BAUD_RATE=57600;
};

#endif
