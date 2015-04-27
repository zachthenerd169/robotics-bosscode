// Software Serial Sample for Packet Serial
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include "DualVNH5019MotorShield.h"

SoftwareSerial SWSerial1(NOT_A_PIN, 14); // RX on no pin (unused), TX on pin 14 (to S1).
SoftwareSerial SWSerial2(NOT_A_PIN, 16);
Sabertooth ST1(128, SWSerial1); // Address 128, and use SWSerial as the serial port.
Sabertooth ST2(128, SWSerial2);

DualVNH5019MotorShield md; // The motor driver for digger actuators

int powerLevels[4] = {20, 50, 90, 127};

void stopIfFault()
{
   if(md.getM1Fault())
   {
     Serial.println("Fault with digger motors"); 
   }
}

void setup()
{
  Serial.begin(9600);
  SWSerial1.begin(9600);
  SWSerial2.begin(9600);
  ST1.autobaud();
  ST2.autobaud();
  ST1.setRamping(55);
  ST2.setRamping(55);
  
  md.init(); // initialize motor driver

}

void loop()
{
  if(Serial.available() > 0) 
  {
    int num = Serial.read();
    int powerLevel = num%4;
    int mode = num/4;
    
    // Stop
    if(mode <= 0)
    {
       stopRobot(); 
    }
    
    // Straight
    else if(mode == 1)  // This is actually turning
    {
       straight(powerLevels[powerLevel]); 
    }
    
    // Backward
    else if(mode == 2)  // This is actually turning
    {
      backward(powerLevels[powerLevel]);  
    }
    
    // Turn Left
    else if(mode == 3)  // This is actually straight or back
    {
      turnRobot(1,powerLevels[powerLevel]);
    }
    
    // Turn Right
    else if(mode == 4) // This is actually straight or back
    {
       turnRobot(-1,powerLevels[powerLevel]); 
    }
    
    
    // Digger Drop
    else if(mode == 5)
    {
      diggerDrop();
    }  
    
     // Digger Up
    else if(mode == 6)
    {
      diggerUp();
    }  
    
    
     // Bucket Dump
    else if(mode == 7)
    {
      bucketDump();
    }  
    
    // Bucket Down
    else if(mode == 8)
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
}



void stopRobot()
{
   ST1.motor(1, 0);
   ST1.motor(2, 0);
}

void straight(int powerLevel)
{
    ST1.motor(1, powerLevel);
    ST1.motor(2, -powerLevel);
}

void backward(int powerLevel)
{
    ST1.motor(1, -powerLevel);
    ST1.motor(2, powerLevel);
}

void turnRobot(int direction, int powerLevel)
{
    ST1.motor(1, direction * powerLevel);
    ST1.motor(2, direction * powerLevel);
}

void diggerUp()
{
   ST2.motor(1, -127);  // Linear actuator out 
   ST2.motor(2, 0);  // Motor on
}

void diggerDrop()
{
   ST2.motor(1, 127);   // Linear actuator in
   ST2.motor(2, 127);    // Motor off
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



