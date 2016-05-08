#include "../CommandBuffer.h"

std::string CommandBuffer::readFromBuffer()
{
	std::string first_command=m_command_queue.front();
	m_command_queue.pop_front();
	return first_command;
	
}
 void CommandBuffer::addToBuffer(std::string data)
 {
 	m_command_queue.push_back(data);
 }
 int CommandBuffer::getSize()
 {
 	return m_command_queue.size();
 }

