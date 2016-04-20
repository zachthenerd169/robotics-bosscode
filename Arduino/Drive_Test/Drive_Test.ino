#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include "SabertoothWrapper.h"
#include "Types.h"

#define MOTOR_SPEED 50

enum DriveState {
  STOP,
  FORWARD,
  BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
};

void setDrive(DriveState s);

SaberWrapper drive_motors(14);

void setup() {
  // put your setup code here, to run once:
  drive_motors.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  setDrive(STOP);
  delay(5000);

  setDrive(FORWARD);
  delay(5000);

  setDrive(STOP);
  delay(1000);

  setDrive(TURN_LEFT);
  delay(3000);

  setDrive(STOP);
  delay(1000);

  setDrive(FORWARD);
  delay(5000);

  setDrive(STOP);
  while (true);

}

void setDrive(DriveState s)
{
  if (s == STOP)
  {
    drive_motors.setMotorOne(0); // stop right motor
    drive_motors.setMotorTwo(0); // stop left motor
  }
  else if (s == FORWARD)
  {
    drive_motors.setMotorOne(MOTOR_SPEED); // right motor forward
    drive_motors.setMotorTwo(MOTOR_SPEED); // left motor forward
  }
  else if (s == BACKWARD)
  {
    drive_motors.setMotorOne(-MOTOR_SPEED); // right motor backward
    drive_motors.setMotorTwo(-MOTOR_SPEED); // left motor backward
  }
  else if (s == TURN_LEFT)
  {
    drive_motors.setMotorOne(MOTOR_SPEED);  // right motor forward
    drive_motors.setMotorTwo(-MOTOR_SPEED); // left motor backward
  }
  else if (s == TURN_RIGHT)
  {
    drive_motors.setMotorOne(-MOTOR_SPEED); // right motor backward
    drive_motors.setMotorTwo(MOTOR_SPEED);  // left motor forward
  }
}
