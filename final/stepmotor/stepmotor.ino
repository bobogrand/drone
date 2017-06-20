// Sketch for Arduino and
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// Adapted by Mallinson-electrical
#define TRUE 1
#define FALSE 0
//declare variables for the motor pins
int motorPin1 = D8;    // Arduino pin 8 to In 1 on the ULN2003
int motorPin2 = D7;    // Arduino pin 9 to In 2 on the ULN2003
int motorPin3 = D6;   // Arduino pin 10 to In 3 on the ULN2003
int motorPin4 = D5;   // Arduino pin 11 to In 4 on the ULN2003
                      // supply power to + and - from Arduino 5vdc and gnd
int motorPin11 = D4;    // Arduino pin 8 to In 1 on the ULN2003
int motorPin22 = D3;    // Arduino pin 9 to In 2 on the ULN2003
int motorPin33 = D2;   // Arduino pin 10 to In 3 on the ULN2003
int motorPin44 = D1;   // Arduino pin 11 to In 4 on the ULN2003


int motorSpeed = 1250;  // set speed of 28BYJ-48 stepper,

//max frequency is 100hz, so max speed is 1250

//(100 steps per second 8 pulses per step so 10000 divided by 8)
// 1250 equates to apx 6 seconds per rev
int count = 0;          // count of steps made
int countt = 0;
int inputs;
int serialFlag=1;
int countsperrev = 510; // number of steps per full revolution- actually 509.5 as gear ratio is 63.684:1 apx
int revolutionsCW = 1; // number of revs required clockwise
int revolutionsCCW = 3; // number of revs required counterclockwise
int lookup[8] = {B01001, B00001, B00011, B00010, B00110,B00100,B01100, B01000};
int setTurnsCW = (revolutionsCW * countsperrev)/2;
int setTurnsCCW = (revolutionsCCW * countsperrev);

void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  pinMode(motorPin11, OUTPUT);
  pinMode(motorPin22, OUTPUT);
  pinMode(motorPin33, OUTPUT);
  pinMode(motorPin44, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Select direction.... 1 or 2");
  Serial.println(setTurnsCW*1.5);
}
/*
void rotate(int dir){
  int i=0;
  if(dir==0){
    for(;i<100;i++){
      anticlockwise();
    }
  }
  else if(dir==1){
    for(;i<100;i++){
      clockwise();
    }
  }
}*/
void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
void setOutputt(int out)
{
  digitalWrite(motorPin11, bitRead(lookup[out], 0));
  digitalWrite(motorPin22, bitRead(lookup[out], 1));
  digitalWrite(motorPin33, bitRead(lookup[out], 2));
  digitalWrite(motorPin44, bitRead(lookup[out], 3));
}

void b_anticlockwise()
{
  for(int i = 0; i < 8; i++) // 8 pulses
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void b_clockwise()
{
  for(int i = 7; i >= 0; i--) // 8 pulses
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void t_anticlockwise()
{
  for(int i = 0; i < 8; i++) // 8 pulses
  {
    setOutputt(i);
    delayMicroseconds(motorSpeed);
  }
}

void t_clockwise()
{
  for(int i = 7; i >= 0; i--) // 8 pulses
  {
    setOutputt(i);
    delayMicroseconds(motorSpeed);
  }
}

void stopwise()
{
  for(int i = 7; i >= 0; i--) // 8 pulses
  {
    delayMicroseconds(motorSpeed);
  }
}

void stepper(int dir){
  /*
  if(dir==1){  // plastic
    if(count < 382){   //move bottom_anticlockwise durint 382
      if(count==1) Serial.println("bottom-anticlockwise");
      b_anticlockwise();
    }
    else if(count < 382 *3){ //move top_anticlockwise durint 382*2
      if(count==382) Serial.println("top-anticlockwise");
      t_anticlockwise();
    }
    else if(count < 100 + 382 *3){ //stop during 100
      stopwise();
    }
    else if(count < 100 + 382 *4){        ////bottom_clockwise durint 382
      if(count==382*3+100) Serial.println("bottom-clockwise");
      b_clockwise();
    }
    else if(count < 100 + 382 *6){        ////top_clockwise durint 382*2
      if(count==382*4+100) Serial.println("top-clockwise");
      t_clockwise();
    }
    else{
      count = 0;
      serialFlag = 1;
    }
    count++;
  }

  if(dir==2){  // can
    if(count < 382){   //move bottom_anticlockwise durint 382
      if(count==1) Serial.println("bottom-clockwise");
      b_clockwise();
    }
    else if(count < 382 *3){ //move top_clockwise durint 382*2
      if(count==382) Serial.println("top-anticlockwise");
      t_anticlockwise();
    }
    else if(count < 100 + 382 *3){ //stop during 100
      stopwise();
    }
    else if(count < 100 + 382 *4){        ////bottom_anticlockwise durint 382
      if(count==382*3+100) Serial.println("bottom-anticlockwise");
      b_anticlockwise();
    }
    else if(count < 100 + 382 *6){        ////top_anticlockwise durint 382*2
      if(count==382*4+100) Serial.println("top-clockwise");
      t_clockwise();
    }
    else{
      count = 0;
      serialFlag = 1;
    }
    count++;
  }

  if(dir==3){
    if(count < 382*2){   //move top_clockwise durint 382*2
      if(count==1) Serial.println("t-clockwise");
      t_clockwise();
    }
    else if(count < 100 + 382 *2){ //stop during 100
      stopwise();
    }
    else if(count < 100 + 382 *4){  //move top_clockwise durint 382*2
      if(count==100 + 382*2) Serial.println("t-anticlockwise");
      t_anticlockwise();
    }
    else{
      count = 0;
      serialFlag = 1;
    }
  count++;
  }
  else
    serialFlag = 1;
}*/
  if(dir==1){
    if(count < 382*2){
      if(count==1) Serial.println("anticlockwise");
      t_anticlockwise();
    }
    else if(count < 382*3){
      stopwise();
    }
    else if(count < 382*5){
      if(count==setTurnsCW) Serial.println("clockwise");
      t_clockwise();
    }
    else{
      count = 0;
      serialFlag = 1;
    }
  count++;
  }
  else if(dir==2){
    if(count < 382*2 ){
      if(count==1) Serial.println("clockwise");
      t_clockwise();
    }
    else if(count < 382*3){
      stopwise();
    }
    else if(count < 382*5){
      if(count==setTurnsCW) Serial.println("anticlockwise");
      t_anticlockwise();
    }
    else{
      count = 0;
      serialFlag = 1;
    }
  count++;
  }
  else
    serialFlag = 1;
}

void loop(){
  if(Serial.available()){
   int input = analogRead(A0);
    if(input > 50){
      
      for (int i = 0; i < samples; i++){
        Serial.println(input);
        input = analogRead(A0);
        
      }
      delay(1000);
    }
    
    if(serialFlag==1 ){
      if(inputs = Serial.parseInt()){
  
        serialFlag = 0;
      }
    }
    if(serialFlag==0){
      stepper(inputs);
    }
  }
}




