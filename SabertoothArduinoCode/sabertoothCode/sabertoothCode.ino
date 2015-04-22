
// Software Serial Sample for Packet Serial
// Copyright (c) 2012 Dimension Engineering LLC
// See license.txt for license details.
#include <SoftwareSerial.h>
#include <Sabertooth.h>
SoftwareSerial SWSerial(NOT_A_PIN, 14); // RX on no pin (unused), TX on pin 11 (to S1).
Sabertooth ST(128, SWSerial); // Address 128, and use SWSerial as the serial port.
int led = 13;
void setup()
{
  Serial.begin(9600);
  SWSerial.begin(9600);
  ST.autobaud();
}

void loop()
{
  if(Serial.available() > 0) 
  {
    int num = Serial.read();
    Serial.println(num, DEC);
    
    if(num == 100)
    {
      digitalWrite(led, HIGH);
      turn(1,100);
    }
    else if(num == 200)
    {
      digitalWrite(led, LOW);
       turn(-1,100); 
    }
    else if(num == 300)
    {
       stop(); 
    }
    else if(num == 400)
    {
       straight(100); 
    }
    else if(num == 500)
    {
      backwards(100);  
    }
  }
}

void turn(int direction, int powerLevel)
{
    ST.motor(1, -direction * powerLevel);
    ST.motor(2, -direction * powerLevel);
}

void stop()
{
   ST.motor(1, 0);
   ST.motor(2, 0);
}

void straight(int powerLevel)
{
    ST.motor(1, powerLevel);
    ST.motor(2, -powerLevel);
}

void backwards(int powerLevel)
{
    ST.motor(1, -powerLevel);
    ST.motor(2, powerLevel);
}

