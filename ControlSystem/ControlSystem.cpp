//============================================================================
// Name        : ControlSystem.cpp
// Description : Main Robot Code
// Compiling   : g++ -Wall -std=c++11 -o ControlSystem.exe ControlSystem.cpp src/ThreaddedNetwork.cpp lib/PracticalSocket.cpp src/Arduino.cpp lib/arduino-serial-lib.cpp -lpthread

//============================================================================
#include <iostream>
#include "ThreaddedNetwork.h"
#include "Arduino.h"
#include <vector>
#include <string>

std::string leftPad(unsigned int num)
{
  //std::cout<<"num: "<<num<<std::endl;
  if(num == 0) {return std::string("000");}
  std::string out="";
  if(num < 10)
  {
    out = "00";
  }
  else if(num < 100)
  {
    out = "0";
  }
  else if(num > 999)
  {
    return "999";
  }
  out += std::to_string(num);
  //std::cout<<"out: "<<out<<std::endl;
  return out;
}

std::string createMotorCommand(unsigned int motor, unsigned int dir, unsigned int power)
{
  std::string out = "!";
  out += motor;
  out += dir;
  out += leftPad(power);
  return out;
}

void handleMovementCommand(std::string cmd, Arduino& motor_arduino)
{
  //std::cout<<"TEST: " << cmd << std::endl;
  char mode = cmd.at(1); // mode is the second letter
  int speed;
  std::cout<<mode<<std::endl;
  std::cout<<cmd.substr(2)<<std::endl;
  if(cmd.length()>2)speed = std::stoi(cmd.substr(2));
  if(mode == '1') // stop
  {
    motor_arduino.write("s");
  }
  else if(mode == '2') // forward
  {
    std::string out = "";
    out += createMotorCommand(0,1,speed); // right forward
    out += createMotorCommand(1,1,speed); // left forward
    std::cout << out << std::endl;
    motor_arduino.write(out);
  }
  else if(mode == '3') // reverse
  {
    std::string out = "";
    out += createMotorCommand(0,0,speed); // right backward
    out += createMotorCommand(1,0,speed); // left backward
    std::cout << out << std::endl;
    motor_arduino.write(out);
  }
  else if(mode == '4') // turn right
  {
    std::string out = "";
    out += createMotorCommand(0,0,speed); // right backward
    out += createMotorCommand(1,1,speed); // left forward
    std::cout << out << std::endl;
    motor_arduino.write(out);
  }
  else if(mode == '5') // turn left
  {
    std::string out = "";
    out += createMotorCommand(0,1,speed); // right forward
    out += createMotorCommand(1,0,speed); // left backward
    std::cout << out << std::endl;
    motor_arduino.write(out);
  }
  else if(mode == '6') // lower bucket
  {
    std::string out = "";
    out += createMotorCommand(3,1,speed); // bucket down
    std::cout << out << std::endl;
    motor_arduino.write(out);
  }
  else if(mode == '7') // raise bucket
  {
    std::string out = "";
    out += createMotorCommand(3,0,speed); // bucket up
    std::cout << out << std::endl;
    motor_arduino.write(out);
  }
}

int main(int argc, char *argv[])
{
  /* Read Command Line Arguments */
  /* Correct Usage: ./ControlSystem.exe 12345 */
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
    exit(1);
  }
  unsigned short server_port = atoi(argv[1]);


  /* Display welcome message */
  std::cout << std::endl
            << "University of Iowa Robotics Club Presents:" << std::endl
            << "2016 NASA Robotic Mining Competition Robot" << std::endl
            << "------------------------------------------" << std::endl
            << std::endl;

  /* Construct robot components */
  ThreaddedNetwork network(server_port);
  //STEPH TEST
  const char* steph_port="/dev/cu.usbmodem1421";
  Arduino motor_arduino(steph_port);

  //USE THIS OTHERWISE
  //Arduino motor_arduino("dev/ttyACM0");


  /* Main program loop */
  while(true)
  {
    /* check for any new messages from the server */
    std::vector<std::string> newMessages = network.getNewMessages();
    if(newMessages.size() > 0)
    {
      /* Processes incoming messages */
      for(unsigned int i=0; i<newMessages.size(); i++)
      {
        /* for now just print the messages */
        std::cout << newMessages.at(i) << std::endl;

        /* pseudo-code */
        switch(newMessages.at(i)[0])
        {
          case 'M': // movement command
            handleMovementCommand(newMessages.at(i), motor_arduino);
            break;
          case 'S': // sensor request
            break;
          case 'I': // image request
            break;
          case 'T': // test message
            break;
          default:  // unknown message
            break;
        }
      }
    }
    network.clearToSend();

    /* Update robot state */
    //

    /* Send back data */
    //
  }
  return 0;
}
