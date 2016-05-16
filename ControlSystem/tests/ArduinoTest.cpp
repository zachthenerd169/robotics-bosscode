#include "../Arduino.h"
//To compile: g++ -std=c++11 -o arduinotest.exe lib/ArduinoTest.cpp tests/ArduinoTest.cpp src/Arduino.cpp 

int main (int argc, char** argv)
{
	const char* steph_port="/dev/cu.usbmodem1421";
	Arduino motor_arduino(steph_port);
	motor_arduino.write("hello motors!");
}
