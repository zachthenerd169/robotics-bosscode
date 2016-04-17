/*
 * AutonomousProcessor.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class Description:
 * States Description:
 * Command Key
 */

#ifndef AUTONOMOUSPROCESSOR_H_
#define AUTONOMOUSPROCESSOR_H_

class AutonomousProcessor :Processor
{
	public:
		/**
		 *
		 */
		void execute()
		{

		}
		/**
		 * Description: reads a commands, interprets/translate, and pass the command along to
		 * 				the appropriate buffer
		 * Input: the command
		 * Output: bool that indicated whethers the command was successfully processed
		 */
		bool processCommand(std::string command);
		/**
		 *
		 */
	private:
		/**
		 * struct will contain all of the sensor objects
		 */
		struct Sensors{
		}m_Sensors;
		//state



};

#endif /* AUTONOMOUSPROCESSOR_H_ */
