/*
 * AutonomousProcessor.h
 *
 *  Created on: Apr 7, 2016
 *      Author: stephaniesmith
 *
 * States Description:
 */

#ifndef AUTONOMOUSPROCESSOR_H_
#define AUTONOMOUSPROCESSOR_H_

class AutonomousProcessor
{
	public:
	 enum
	 {
		 DIG,
		 FIND_BEACON,
		 GOTO_BUCKET,
		 GOTO_DIG_SITE,
		 WIN,
		 STOP,
	 }states;

	private:


};

#endif /* AUTONOMOUSPROCESSOR_H_ */
