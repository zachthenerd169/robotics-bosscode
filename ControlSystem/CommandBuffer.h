/*
 *  CommandBuffer.h
 *  Created on: Apr 10, 2016
 *  Author: stephaniesmith
 *
 *  Class description:
 */

#include <iostream>
#include <string.h>
#include <deque>

#ifndef COMMANDBUFFER_H_
#define COMMANDBUFFER_H_

class CommandBuffer : Buffer
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
		 *
		 */
		std::deque<std::string> m_command_queue;

};



#endif /* COMMANDBUFFER_H_ */
