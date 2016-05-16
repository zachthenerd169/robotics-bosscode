#include "../Arduino.h"
//To compile: g++ -std=c++11 -o arduinotest.exe lib/ArduinoTest.cpp tests/ArduinoTest.cpp src/Arduino.cpp 

int main (int argc, char** argv)
{
	Arduino arduino();
	arduino.writeToMotors("hello motors!");
}
