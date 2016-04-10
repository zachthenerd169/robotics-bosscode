/*
 * CommandBuffer.h

 *Created on: Apr 10, 2016
 *      Author: stephaniesmith
 */

#include <iostream>
#include <string.h>
#include <deque>

#ifndef COMMANDBUFFER_H_
#define COMMANDBUFFER_H_

class CommandBuffer : Buffer
{
	public:
		//
		// adds the command to the end of the queue
		//
		std::string readFromBuffer();
		//
		// removes command from the beginning of the queue
		//
		void  addToBuffer(std::string command);
		//
		// returns the number of elements in the buffer
		//
		int getSize();

	private:
		std::deque<std::string> m_command_queue;

};



#endif /* COMMANDBUFFER_H_ */
