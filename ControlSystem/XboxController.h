/*
 * XboxController.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 */

#ifndef XBOXCONTROLLER_H_
#define XBOXCONTROLLER_H_

class XboxController : UserController
{
	public:
		bool processInput();
	private:
		struct ControllerState
		{
			bool endA;
			bool endB;
			bool endX;
			bool endY;
			bool endUp;
			bool endDown;
			bool endStart;
			bool endRB;
			bool endLB;
			bool endRThumb;
			bool endLThumb;
		};

};





#endif /* XBOXCONTROLLER_H_ */
