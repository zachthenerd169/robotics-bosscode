void setup() 
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) { // wait for serial port to connect. Needed for native USB port only
  }
  //pinMode(2, INPUT);   // digital sensor is on digital pin 2
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() 
{
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) 
  {
    // get incoming byte:
   String inString = Serial.readString();
   Serial.println("Arduino received: " + inString);
   Serial.println("Arduino Says: Hi laptop!");
  }
}

void establishContact() {
  while (Serial.available() <= 0) 
  {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}


