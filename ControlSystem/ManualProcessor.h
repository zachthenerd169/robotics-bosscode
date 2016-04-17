/*
 * ManualProcessor.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class Description: ManualProcessor
 */
#include<memory> //for smart pointers
#ifndef MANUALPROCESSOR_H_
#define MANUALPROCESSOR_H_


class ManualProcessor
{
	public:
		/**
		 * Description: intializes all of the buffers to the different buffer objects and autonomous is not
		 * 				initially on by default
		 * Input: 3 buffer objects
		 */
		ManualProcessor(const CommandBuffer& command_buffer, const CommandBuffer& autonomous_buffer,
				const DataBuffer& data_buffer, const CommandBuffer& central_control_buffer, bool autonomous_on=false):m_command_buffer(command_buffer), m_data_buffer(data_buffer),
				m_autonomous_buffer(autonomous_buffer), m_central_control_buffer(central_control_buffer),
				m_autonomous_on(autonomous_on){}
		/**
		 * Description: default constructor
		 * Input: optionally can initialize autonomous to be on
		 */
		ManualProcessor(bool autonomous_on=false):m_command_buffer(nullptr), m_data_buffer(nullptr), m_autonomous_buffer(nullptr),
				m_central_control_buffer(nullptr), m_autonomous_on(autonomous_on){}
		/**
		 * Description: reads a commands, interprets/translate, and pass the command along to
		 * 				the appropriate buffer
		 * Input: the command
		 * Output: bool that indicated whethers the command was successfully processed
		 */
		bool processCommand(std::string command);
		/**
		 * Description: sets a command in the m_autonomous_buffer in order to turn autonomous on
		 * Input: none
		 * Output: bool indicates if autonomous was turned on successfully
		 */
		bool startAutonomous();
		/**
		 * Description: sets a command in the m_autonomous_buffer in order to turn the autonomous
		 * 				off
		 * Input: by default the autonomous will stop safely. A 'safe stop' means that the
		 * 		  autonomous will finish up whatever it's doing and then stop, so if the stop is
		 * 		  not safe, it will quit mid-task.
		 * Output: bool indicates if autonomous was turned off successfully
		 */
		bool stopAutonomous(bool safe_stop=true);
	private:
		/**
		 * buffer between Network and ManualController (data sent to ManualProcessor from Network)
		 */
		std::shared_ptr<CommandBuffer> m_command_buffer;
		/**
		 * buffer between Network and ManualController (data sent to Network from ManualProcessor
		 */
		std::shared_ptr<DataBuffer> m_data_buffer;
		/**
		 * buffer between AutonomousProcessor and ManualProcessor (ManualProcessor will send
		 * data to AutonomousProcessor
		 */
		std::shared_ptr<CommandBuffer> m_autonomous_buffer;
		/**
		 * buffer between ManualProcessor and CentralController (ManualProcessor will send
		 * data to CentralController)
		 */
		std::shared_ptr<CommandBuffer> m_central_control_buffer;
		/**
		 * keeps track of whether AutonomousProcessor is currently communicating with
		 * CentralController or not
		 */
		bool m_autonomous_on;
};
#endif /* MANUALPROCESSOR_H_ */
