/*
 * Buffer.h
 * Created on: Apr 7, 2016
 * Author: stephaniesmith
 *
 * Class Description: Buffer provides an interface CommandBuffer and DataBuffer.
 * 					  Buffer outlines how to interact with the underlying
 * 					  datatpye.
 *
 */

#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer
{
	public:
		virtual ~Buffer() {} //make virtual to ensure that actual instantiated object is destructed
		/**
		 * Description: reads data from the buffer and then removes it from the
		 * 				buffer
		 * Input: none
		 * Output: whatever data is returned from the buffer (determined by derived class)
		 */
		virtual void* readFromBuffer() = 0;
		/**
		 * Description: adds data to the buffer
		 * Input: whatever data is added to the buffer (determined by the derived class)
		 * Output: none
		 */
		virtual void addToBuffer(void* val) = 0;
		/**
		 * Description: determines how many elements are in the buffer
		 * Input: none
		 * Output: how many elements are in the buffer
		 */
		virtual int  getSize() = 0;
};
#endif /* BUFFER_H_ */
