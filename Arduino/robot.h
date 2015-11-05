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
 *   3. (!)implement the actual motor movements using saberteeth
 */

 #define FULL_SPEED 255
 #define TURN_SPEED 100
 #define ROTATE_SPEED 255

class Motor {
public:
  void setSpeed(int speed) { m_speed = speed; }
  void stop() { setSpeed(0); }
private:
  int m_speed;
}

class Robot {
public:
  /* Set the robot speed and direction, then update the motors to reflect the change */
  void move(int speed, int direction){
    m_speed = speed;
    m_direction = direction;
    updateMotors();
  }
  
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
  int m_speed;
  int m_direction;
  Motor m_left_motor;
  Motor m_right_motor;

  void updateMotors(){
    m_left_motor.setSpeed(m_speed+m_direction);
    m_right_motor.setSpeed(m_speed-m_direction);
  }
}
