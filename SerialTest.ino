/*
 * Hello World!
 *
 * This is the Hello World! for Arduino. 
 * It shows how to send data to the computer
 */
int led = 11;

void setup()                    // run once, when the sketch starts
{
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  //Serial.begin(9600);           // set up Serial library at 9600 bps
  
  //Serial.println("Hello world!");  // prints hello with ending line break 
}

void loop()                       // run over and over again
{
  //if(Serial.available() > 0) 
  //{
    //turnOn();
  //}
}

void turnOn()
{
  digitalWrite(led, HIGH);
}
