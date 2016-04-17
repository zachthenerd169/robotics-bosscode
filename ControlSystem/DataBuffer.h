/*
 * DataBuffer.h
 * Created on: Apr 10, 2016
 * Author: stephaniesmith
 *
 * Class description: DataBuffer holds data that generally move from robot to the external
 *                    processors (whether its autonomous or manual). The underlying data
 *  				  type is a queue of strings. It is up to the classes that use the Data
 *  				  Buffer to interpret the strings as different data types if necessary.
 */

#ifndef DATABUFFER_H_
#define DATABUFFER_H_

class DataBuffer
{
	public:
		/**
		 * Description: removes data from the beginning of the queue
		 * Input: none
		 * Output: data
		 */
		std::string readFromBuffer();
		/**
		 * Decription: adds data to the end of the queue
		 * Input: the data to be added to the queue
		 * Output: none
		 */
		 void addToBuffer(std::string data);
		 /**
		  * Description: returns the number of elements in the buffer
		  * Input: none
		  * Output: number of elements in the buffer
		  */
		 int getSize();
	private:
		 /**
		  * queue of strings
		  */
		 std::deque<std::string> m_command_queue;


};
#endif /* DATABUFFER_H_ */
