/*
 * DataBuffer.h
 *
 *  Created on: Apr 10, 2016
 *      Author: stephaniesmith
 */

#ifndef DATABUFFER_H_
#define DATABUFFER_H_

class DataBuffer
{
	public:
		//
		// adds the command to the end of the queue
		//
		bool readFromBuffer(std::string data);
		//
		// removes command from the beginning of the queue
		//
		std::string addToBuffer();
		//
		// returns the number of elements in the buffer
		//
		int getSize();

	private:
		std::deque<std::string> m_data_queue;
};
#endif /* DATABUFFER_H_ */
