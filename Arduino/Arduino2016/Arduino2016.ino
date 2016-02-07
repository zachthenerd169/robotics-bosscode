// Software Serial Sample for Packet Serial
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include "DualVNH5019MotorShield.h"
#include <Servo.h> //for testing only

SoftwareSerial SWSerial1(NOT_A_PIN, 14); // RX is NOT_A_PIN (unused), TX on pin 14 (to S1).
SoftwareSerial SWSerial2(NOT_A_PIN, 16); //RX is NOT_A_PIN (unused), TX on pin 16 (to S2)

Sabertooth ST1(128, SWSerial1); //Address 128, and use SWSerial as the serial port.
Sabertooth ST2(128, SWSerial2); //ST1 controls treads/wheels (2 motors), ST2 controls digger (1 linear actuator and 1 motor)

DualVNH5019MotorShield md; //md controls bucket (two linear actuators)
Servo servo;

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
  servo.attach(13);
}

void loop()
{
    while (Serial.available() == 0)  {} //wait until there is something to read
    int mode = Serial.read(); //read the mode
    int powerLevel = 0;
    
    if (mode >= 2 && mode <= 5) //if the user wants chooses mode 2-5, they need to set the power
    {
      while(Serial.available() == 0) {} //wait for another command to set the power level
      powerLevel = Serial.read();
        
    }
    if(mode == 1) { moveRobot(0); }//stop robot
    else if(mode == 2)  {moveRobot(powerLevel);}//move straight forward
    else if(mode == 3)  {moveRobot(powerLevel, -1, -1);}
    else if(mode == 4)  // This is actually straight or back
    {
      turnRobot(1, powerLevel);
    }   
    else if(mode == 5) // This is actually straight or back
    {
       turnRobot(-1, powerLevel); 
    }
    else if(mode == 6) //drop digger
    {
      diggerDrop();
    }  
    else if(mode == 7) //raise digger
    {
      diggerUp();
    }  
    else if(mode == 8) //dump bucket
    {
      bucketDump();
    }  
    else if(mode == 9) //put bucket back down
    {
      bucketDown();
    }  

    servo.write(powerLevel);
    delay(20);
    //digitalWrite(13,HIGH);
    //delay(700);
    //digitalWrite(13, LOW);
    Serial.println("Arduino Received: " + String(mode, DEC) + " " + String(powerLevel, DEC));
}

void moveRobot(int powerLevel, short dir1=1, short dir2=1)
{
  ST1.motor(1, dir1*powerLevel);
  ST1.motor(2, dir2*powerLevel);
}

/*void stopRobot()
{
    ST1.motor(1, 0); 
    ST1.motor(2, 0);
}*/
void straight(int powerLevel)
{
    ST1.motor(1, powerLevel);
    ST1.motor(2, powerLevel);
}

void backward(int powerLevel)
{
   ST1.motor(1, -powerLevel);
   ST1.motor(2, -powerLevel);
}

void turnRobot(int direction, int powerLevel)
{
   ST1.motor(1, -direction * powerLevel);
   ST1.motor(2, direction * powerLevel);
}

void diggerUp()
{
   // 127 is the default power level
   ST2.motor(1, -127);  // Linear actuator out 
   ST2.motor(2, 0);  // Motor off
}

void diggerDrop()
{
   // 127 is the default power level
   ST2.motor(1, 127);   // Linear actuator in
   ST2.motor(2, 70);    // Motor on
}

void bucketDump()
{
   // 400 is the default speed
   md.setSpeeds(-400, -400);
   //md.setSpeeds(-400, -400);  // Linear actuators up
   stopIfFault();
}

void bucketDown()
{
   // 400 is the default speed
   md.setSpeeds(400, 400);  // Linear actuators down
   stopIfFault();
}
