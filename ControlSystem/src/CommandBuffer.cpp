#include "CommandBuffer.h";

std::string CommandBuffer::readFromBuffer()
{
	return m_command_queue.pop_font();
}
