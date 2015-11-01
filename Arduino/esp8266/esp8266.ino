#include <SoftwareSerial.h>
const byte rxPin=2;
const byte txPin=3;
SoftwareSerial esp8266 = SoftwareSerial(rxPin,txPin); //set up RX and TX pins

//TX pin is 3 --> goes to RX on esp8266
//RX is 2 --> goes to TX on esp8266
void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  esp8266.begin(9600);
}


void loop() {
  if(esp8266.available())
  {
    Serial.println("esp is  available");
    while(esp8266.available())
    {
      char c = esp8266.read();
      Serial.write(c);
    }
    
  }
  if(Serial.available())
  {
    Serial.write('c');
    Serial.println("does this work");
    delay(1000);
    String command="";
    while(Serial.available())
    {
      command+=(char)Serial.read();
    }
    Serial.println(command);
    esp8266.write('a');
  }
  // put your main code here, to run repeatedly:

}
