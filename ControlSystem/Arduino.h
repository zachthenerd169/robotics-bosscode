#ifndef ARDUINO_H_
#define ARDUINO_H_

class Arduino{
	
	public:
		/**
		 * Description: writes the string to the arduino
		 * Input: the message to be written
		 */
		std::string writeToMotors(std::string message);

	private:
		int m_motor_serial_port;	
};

#endif
