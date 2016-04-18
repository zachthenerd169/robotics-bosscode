/*
 *  CommandBuffer.h
 *  Created on: Apr 10, 2016
 *  Author: stephaniesmith
 *
 *  Class description: CommandBuffer holds data that generally move from the external processors
 *  					(whether its autonomous or manual) to the robot. The underlying data
 *  					type is a queue of strings. It is up to the classes that use the Command
 *  					buffer to interpret the strings as different data type if necessary.
 */

#include <iostream>
#include <string.h>
#include <deque>

#ifndef COMMANDBUFFER_H_
#define COMMANDBUFFER_H_

class CommandBuffer : public Buffer
{
	public:
		/**
		 * Description: reads the data from the top of the queue and removes it (dequeue)
		 * Input: none
		 * Output: string
		 */
		std::string readFromBuffer();
		/**
		 * Description: adds the data to the end of the queue (enqueue)
		 * Input: string command to be sent
		 * Output: none
		 */
		void  addToBuffer(std::string command);
		/**
		 * Description: gets the number of elements in the queue
		 * Input: none
		 * Output: the number of elements in the queue
		 */
		int getSize();

	private:
		/**
		 * queue of strings
		 */
		std::deque<std::string> m_command_queue;

};



#endif /* COMMANDBUFFER_H_ */
