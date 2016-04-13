/*
 * ManualProcessor.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 */
#include<memory>
#ifndef MANUALPROCESSOR_H_
#define MANUALPROCESSOR_H_


class ManualProcessor
{
	public:
		ManualProcessor(const CommandBuffer& command_buffer, const CommandBuffer& autonomous_buffer,
				const DataBuffer& data_buffer):m_command_buffer(command_buffer), m_data_buffer(data_buffer),
				m_autonomous_buffer(autonomous_buffer), m_autonomous_on(false){}

		bool processCommand(std::string command);
		bool startAutonomous();
		bool stopAutonomous(bool safe_stop=false);
	private:
		std::shared_ptr<CommandBuffer> m_command_buffer;
		std::shared_ptr<DataBuffer> m_data_buffer;
		std::shared_ptr<CommandBuffer> m_autonomous_buffer;
		bool m_autonomous_on;
};


#endif /* MANUALPROCESSOR_H_ */
