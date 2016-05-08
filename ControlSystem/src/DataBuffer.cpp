#include "../DataBuffer.h"

std::string DataBuffer::readFromBuffer()
{
	std::string first_command=m_data_queue.front();
	m_data_queue.pop_front();
	return first_command;
	
}
 void DataBuffer::addToBuffer(std::string data)
 {
 	m_data_queue.push_back(data);
 }
 int DataBuffer::getSize()
 {
 	return m_data_queue.size();
 }
