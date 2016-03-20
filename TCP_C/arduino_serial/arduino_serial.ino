

void setup() 
{
  pinMode(13,OUTPUT);
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) { // wait for serial port to connect. Needed for native USB port only
  }
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() 
{
  // if we get a valid byte, read analog ins:
  while (Serial.available() > 0) 
  {}
    // get incoming byte
    byte inString = Serial.read();
    byte inString2 = 0;
    while(Serial.available()>0){}
    
      inString2 = Serial.read();
     
      
          digitalWrite(13,HIGH);
          delay(700);
          digitalWrite(13, LOW);
      
    
    //Serial.println("Arduino Received: " + String(inString, DEC)+" " + String(inString2, DEC));
   //Serial.write(60);
   
   Serial.println("Arduino Received: " + String(inString, DEC)+" " + String(inString2, DEC));
   //Serial.println("Arduino Says: Hi laptop!");
  
}

void establishContact() {
  while (Serial.available() <= 0) 
  {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}


