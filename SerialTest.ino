/*
 * Hello World!
 *
 * This is the Hello World! for Arduino. 
 * It shows how to send data to the computer
 */
 
 #include <Servo.h>
int led = 13;
Servo myservo;

void setup()                    // run once, when the sketch starts
{
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  myservo.attach(9);
  Serial.println("Hello world!");  // prints hello with ending line break 
}

void loop()                       // run over and over again
{
  if(Serial.available() > 0) 
  {
    float num = Serial.parseFloat();
    if(num < 180 || num > 0)
    {
      myservo.write(num);
    }
    if(num == 200)
    {
      turnOn();
    }
  }
}

void turnOn()
{
  delay(1000);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}
