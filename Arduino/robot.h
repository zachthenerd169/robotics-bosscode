/*
 * Title: Arduino Robot Movement Code
 * Project: UIowa - NASA RMC 2016
 * Author(s): Zach Williamson
 * Created On: 11/5/15
 *
 * Description: Creates two useful classes, Motor and Robot.  Motor represents
 * a simple motor capable of moving forwards and backwards at a user defined
 * speed.  Robot represents the drive-train of a robot with the ability to move
 * forwards, backwards, bank left or right, and spin in place.
 *
 * Todo:
 *   1. rename the Robot class to something more descriptive like DriveTrain
 *   2. allow Robot/DriveTrain to have it's maximum speed set at runtime
 *   3. should the code int robot.initalize() be put into a constructor instead?
 *   4. add range checks to setSpeed()
 */

#include <SoftwareSerial.h>
#include <Sabertooth.h>

#define FULL_SPEED 255
#define TURN_SPEED 100
#define ROTATE_SPEED 255

/* Motor Class:
 * Provide an abstraction for working with motors attatched to a sabertooth
 * motor controller.
 */

class Motor {
public:
  void Motor(Sabertooth *sabertooth, int motorNumber){
    m_sabertooth = sabertooth;
    m_motorNumber = motorNumber;
  }

  void setSpeed(int speed) { 
    m_speed = speed; 
    m_sabertooth->motor(m_motorNumber, speed);
  }

  void stop() { setSpeed(0); }
private:
  int m_speed;
  Sabertooth *m_sabertooth;
  int m_motorNumber;
};

/* Robot Class:
 * Provide a single, high-level interface for robot movements.  
 */

class Robot {
public:
  /* Initalize all of the objects needed to run the robot */
  void initialize(){
    m_port = new SoftwareSerial(NOT_A_PIN,14); // set up serial port
    m_port.begin(9600);

    m_sabertooth = new Sabertooth(128, port); // set up sabertooth
    m_sabertooth.autobaud();
    m_sabertooth.setRamping(55);

    m_left_motor = new Motor(&m_sabertooth,1); // set up motors
    m_right_motor = new Motor(&m_sabertooth,2);
    m_speed = 0;
    m_direction = 0;
    updateMotors();
  }

  /* Set the robot speed and direction, then update the motors to reflect the 
   * change 
   */
  void move(int speed, int direction){
    m_speed = speed;
    m_direction = direction;
    updateDriveMotors();
  }
  
  /* define drive movements */
  void stop()           { move(0,0); }                     //stop moving
  void forward()        { move(FULL_SPEED,0); }            //forward at full speed
  void backward()       { move(-FULL_SPEED,0); }           //backward at full speed
  void forwardLeft()    { move(FULL_SPEED,-TURN_SPEED); }  //forward and bank left
  void forwardRight()   { move(FULL_SPEED, TURN_SPEED); }  //forards and bank right
  void backwardLeft()   { move(-FULL_SPEED,-TURN_SPEED); } //backward and bank left
  void backwardRight()  { move(-FULL_SPEED,TURN_SPEED); }  //backward and bank right
  void spinLeft()       { move(0,-ROTATE_SPEED); }         //spin left
  void spinRight()      { move(0,ROTATE_SPEED); }          //spin right

private:
  /* private member variables */
  int m_speed;
  int m_direction;
  SoftwareSerial m_port;
  Sabertooth m_sabertooth;
  Motor m_left_motor;
  Motor m_right_motor;

  /* set the drive motors to the correct speed for the current motion */
  void updateDriveMotors(){
    m_left_motor.setSpeed(m_speed+m_direction);
    m_right_motor.setSpeed(m_speed-m_direction);
  }
};
