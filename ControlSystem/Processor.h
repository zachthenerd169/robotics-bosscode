/*
 * Processor.h
 * Created on: Apr 17, 2016
 * Author: stephaniesmith
 *
 * Class Description: base class for AutonomousProcessor and ManualProcessor. This class processes
 *                    the commands and passes it to the CentralController
 *
 */
#ifndef PROCESSOR_H_
#define PROCESSOR_H_

class Processor
{
	public:
		/**
		 * Description: constructs processor
		 * Input: a CommandBuffer reference
		 */
		Processor(const CommandBuffer& central_control_buffer):
			m_central_control_buffer(central_control_buffer),
			autonomous_states(STOP){}
		/**
		 * Description: default constructor
		 * Input: none
		 */
		Processor():m_central_control_buffer(nullptr), autonomous_states(STOP){};
		virtual ~Processor();
		/**
		 *Description: reads a commands, interprets/translate, and pass the command along to
		 * 				the appropriate buffer
		 * Input: the command
		 * Output: bool that indicated whethers the command was successfully processed
		 */
		virtual bool processCommand(std::string command)=0;
		/**
		 * Description: reads the values from all of the sensors
		 * Input: none
		 * Output: all of the sensor values
		 */
		//this may not return a string
		std::string readFromAllSensors();
		/**
		 * Description: gets the m_central_control_buffer so that it can be accessed by its
		 * 				derived classes
		 * Input: none
		 * Output: a CommandBuffer reference
		 */
		std::shared_ptr<CommandBuffer> getCentralControlBuffer(){return m_central_control_buffer;}
		/**
		 * Description: sets the m_central_control_buffer to a CommandBuffer reference
		 * 				(this will typically used if Processeor is constructed with a default
		 * 				constructor)
		 * 	Input: a CommandBuffer reference
		 * 	Output: none
		 */
		void setCentralControlBuffer(const CommandBuffer& central_control_buffer){m_central_control_buffer=central_control_buffer;}
	private:
    /**
	 * buffer between ManualProcessor and CentralController (ManualProcessor will send
	 * data to CentralController)
	 */
	std::shared_ptr<CommandBuffer> m_central_control_buffer;

	protected:
		/**
		 * The different states AutonomousProcessor is in. It's in the interest of the
		 * ManualProcessor to know these states too.
		 */
		 enum
		 {
			 DIG,
			 FIND_BEACON,
			 GOTO_BUCKET,
			 GOTO_DIG_SITE,
			 WIN,
			 STOP,
		 }autonomous_states;
		 /**
		  * struct will contain all of the sensor objects
		  */
		 struct Sensors{
		 		}m_Sensors;
		 		//state

};


#endif /* PROCESSOR_H_ */
