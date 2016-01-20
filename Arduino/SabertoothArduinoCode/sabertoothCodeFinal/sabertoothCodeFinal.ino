// Software Serial Sample for Packet Serial
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include "DualVNH5019MotorShield.h"

SoftwareSerial SWSerial1(NOT_A_PIN, 14); // RX is NOT_A_PIN (unused), TX on pin 14 (to S1).
SoftwareSerial SWSerial2(NOT_A_PIN, 16); //RX is NOT_A_PIN (unused), TX on pin 16 (to S2)

Sabertooth ST1(128, SWSerial1); //Address 128, and use SWSerial as the serial port.
Sabertooth ST2(128, SWSerial2); //ST1 controls treads/wheels (2 motors), ST2 controls digger (1 linear actuator and 1 motor)

DualVNH5019MotorShield md; //md controls bucket (two linear actuators)

void stopIfFault()
{
   if(md.getM1Fault() || md.getM2Fault()){Serial.println("Fault with digger motors");} //client won't be able to receive for now
}
void setup()
{
  Serial.begin(9600); //for communicating with NUC
  SWSerial1.begin(9600); //for communicating with sabertooth #1 (wheels)
  SWSerial2.begin(9600); //for comminicating with sabertooth #2 (digger)
  ST1.autobaud(); //delay to give driver time to start up
  ST2.autobaud(); //delay to give driver time to start up
  ST1.setRamping(55); //-1683 (slowest)
  ST2.setRamping(55);
  
  md.init(); // initialize motor driver

}

void loop()
{
  while (Serial.available() == 0)  {} //wait until there is something to read
  
    int num = Serial.read(); //read the mode
    int powerLevel1 = 0; 
    int powerLevel2 = 0;
    int mode = num;
    
    if (mode >= 1 && mode <= 4) //if the user wants chooses mode 1-4, they need to set the power
    {
      while(Serial.available() == 0) {} //wait for another command to set the power level
        powerLevel1 = Serial.read();
        
      while(Serial.available() <= 0) {} //why <=0 and not == 0?
        powerLevel2 = Serial.read();
    }
    if(mode <= 0) //Stop
    {
       stopRobot();
    }
    else if(mode == 1)  //turning which direction?
    {
       straight(powerLevel1, powerLevel2); 
    }
    else if(mode == 2)  //turing which direction?
    {
      backward(powerLevel1, powerLevel2);  
    }
    else if(mode == 3)  // This is actually straight or back
    {
      turnRobot(1, powerLevel1, powerLevel2);
    }   
    else if(mode == 4) // This is actually straight or back
    {
       turnRobot(-1, powerLevel1, powerLevel2); 
    }
    else if(mode == 5) //drop digger
    {
      diggerDrop();
    }  
    else if(mode == 6) //raise digger
    {
      diggerUp();
    }  
    else if(mode == 7) //dump bucket
    {
      bucketDump();
    }  
    else if(mode == 8) //put bucket back down
    {
      bucketDown();
    }  
    /*
     // Strafe right
    else if(mode == 9)
    {
      strafeRight();
    }  
    
     // Strafe left
    else if(mode == 10)
    {
      strafeLeft();
    }  
    */
}



void stopRobot()
{
   ST1.motor(1, 0); 
   ST1.motor(2, 0);
}
void straight(int powerLevel1, int powerLevel2)
{
    ST1.motor(1, powerLevel1);
    ST1.motor(2, powerLevel2);
}

void backward(int powerLevel1, int powerLevel2)
{
    ST1.motor(1, -powerLevel1);
    ST1.motor(2, -powerLevel2);
}

void turnRobot(int direction, int powerLevel1, int powerLevel2)
{
    ST1.motor(1, -direction * powerLevel1);
    ST1.motor(2, direction * powerLevel2);
}

void diggerUp()
{
   ST2.motor(1, -127);  // Linear actuator out 
   ST2.motor(2, 0);  // Motor off
}

void diggerDrop()
{
   ST2.motor(1, 127);   // Linear actuator in
   ST2.motor(2, 70);    // Motor on
}

void bucketDump()
{
   md.setSpeeds(-400, -400);  // Linear actuators up
   stopIfFault();
}

void bucketDown()
{
   md.setSpeeds(400, 400);  // Linear actuators down
   stopIfFault();
}




