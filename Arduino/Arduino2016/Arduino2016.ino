/**
 * Arduino program receives a serial input from the NUC (via the usb port), and then executes the desired command.
 * The 3 main commands the arduino should receive are:
 *  1) driving the robot
 *  2) operating the digger
 *  3) dumping/lowering the bucket
 *  
 *  The arduino accomplishes these commands by commounicating with 3 motor controllers. 
 *  There are two sabertooth motor controllers (ST1 & ST2) that control the wheels\treads and digger.
 *  There is one arduino motor sield (md) that controls the bucket
 *  
 *  Here is the documentation of the sabertooth motor controllers: http://www.dimensionengineering.com/products/sabertooth2x32 (specs)
 *                                                                 https://www.dimensionengineering.com/info/arduino (arduino interface)
 *  Here is the documentatiom of the arduino motor shield: https://www.arduino.cc/en/Main/ArduinoMotorShieldR3
 *  
 *  The arduino will allow send data to the NUC if there is a fault in the motor shield
 */
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include "DualVNH5019MotorShield.h"

SoftwareSerial SWSerial1(NOT_A_PIN, 14); // RX is NOT_A_PIN (unused), TX on pin 14 (to S1).
SoftwareSerial SWSerial2(NOT_A_PIN, 16); //RX is NOT_A_PIN (unused), TX on pin 16 (to S2)
Sabertooth ST1(128, SWSerial1); //Address 128, and use SWSerial as the serial port.
Sabertooth ST2(128, SWSerial2); //ST1 controls treads/wheels (2 motors), ST2 controls digger (1 linear actuator and 1 motor)
DualVNH5019MotorShield md; //md controls bucket (two linear actuators)

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
/**
 * processing user input
 * Do serial event instead?
 */
void loop()
{
    while (Serial.available() == 0)  {} //wait until there is something to read
    int mode = Serial.read(); //read the mode
    int powerLevel = 0;
    if (mode >= 2 && mode <= 5) //if the user wants chooses mode 2-5, they need to set the power (these modes move the robot)
    {
      while(Serial.available() == 0) {} //wait for another command to set the power level
      powerLevel = Serial.read(); //reading the power level
    }
    //FSM
    if(mode == 1) { moveRobot(0,1,1); }//stop robot
    else if(mode == 2)  {moveRobot(powerLevel,1,1);}//move straight forward
    else if(mode == 3)  {moveRobot(powerLevel, -1, -1);} //move robot in reverse
    else if(mode == 4)  {moveRobot(powerLevel, -1, 1); } //turn robot right //turnRobot(1, powerLevel);
    else if(mode == 5)  {moveRobot(powerLevel, 1, -1); } // //turn robot left  turnRobot(-1, powerLevel);
    else if(mode == 6){diggerDrop();} //drop digger
    else if(mode == 7){diggerUp();} //raise digger
    else if(mode == 8){moveBucket(-1);} //dump bucket 
    else if(mode == 9){moveBucket(1);} //put bucket back down
}
/**
 * Function stops the robot, turns the robot right/left, 
 * and moves the robot straight/reverse
 * 
 * the motor controller controlling the wheels on the robot is sabertooth ST1
 * 
 * motor #1 controls the right wheel
 * motor #2 controls the left wheel
 * 
 * power level range: 
 * suggested power levels: 
 */
void moveRobot(int powerLevel, short dir1, short dir2)
{
  ST1.motor(1, dir1*powerLevel);
  ST1.motor(2, dir2*powerLevel);
}
/**
 * Functions diggerUp and diggerDrop operate the digger --> one of the motors is a linear actuator to raise/lower the digger; the other motor is a CIM that does the digging
 * 
 * the motor controller controlling the digger on the robot is sabertooth ST2
 * 
 * motor #1 controls the linear actuator
 * motor #2 controls the CIM (digging operations)
 */
void diggerUp()
{
   ST2.motor(1, -127); //Linear actuator out  //127 is the default power level
   ST2.motor(2, 0);  //Motor off
}
void diggerDrop()
{
   ST2.motor(1, 127);//Linear actuator in //127 is the default power level
   ST2.motor(2, 70);//Motor on
}
/**
 * Function raises and lowers the bucket
 * 
 * the motor controller controlling the bucket is the arduino shield
 * 
 * The motor shield has to separate channels: A & B. Each channel control a linear actuator.
 */
void moveBucket(short dir){md.setSpeeds(dir*400, dir*400);}
/**
 * If either of the channels experience faults --> do what? should we just return something back to the client, 
 * or should we stop both actuators (this would be preferable)
 */
void stopIfFault()
{
   if(md.getM1Fault() || md.getM2Fault()){Serial.println("FAULT: MOTOR SHIELD (DIGGERS)");} //client won't be able to receive for now
}
