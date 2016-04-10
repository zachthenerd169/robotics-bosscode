/*
 * Buffer.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer
{
	public:
		virtual ~Buffer() {}
		virtual void * readFromBuffer() = 0;
		virtual void addToBuffer() = 0;
		virtual int  getSize() = 0;
};
#endif /* BUFFER_H_ */
