void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  run();
  readInput();
}

void readInput(){
  if(Serial.available()>0){
     int input = Serial.read();
     //here we might need a stop command. Example
     /*if (input == 33){//stops if ! comes through serial
      dir = 0;
    }*/
  }
}
void run(){
  //here we put the code that determines what to do when running
}
