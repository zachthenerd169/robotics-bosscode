/* Zach Notes: for IR sensor 1 send 'i1' for IR sensor 2 send 'i2'
 *  
 */

#define IR_MAX 60
#define IR_MIN 10

char in_byte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  waitForSerial(); // Wait for serial communication to begin
  in_byte = Serial.read();
  switch(in_byte)
  {
    case 'i':
      handleIR();
      break;
  }
}

void handleIR()
{
  waitForSerial();
  in_byte = Serial.read();
  float distance = 0;
  switch(in_byte)
  {
    case '1':
      distance = readIR(0);
      break;
    case '2':
      distance = readIR(1);
      break;
  }
  char out = (distance - IR_MIN)/(IR_MAX-IR_MIN)*255;
  Serial.println(out);
}

void waitForSerial()
{
  while(!Serial.available());
}

int analogReadAvg(int pin, int samples=3, int delayus=10)
{
  long sum = 0;
  for(int i = 0; i<samples; i++)
  {
    sum += analogRead(pin);
    delayMicroseconds(delayus);
  }
  return sum/samples;
}

float readIR(int pin)
{
  float volts = (float(analogReadAvg(pin,100,0))*5.0)/1024.0;
  if(volts > 5/IR_MIN){
    return IR_MIN;
  }
  if(volts < 5/IR_MAX)
  {
    return IR_MAX;
  }
  float distance = 24.0/volts;
  return distance;
}
