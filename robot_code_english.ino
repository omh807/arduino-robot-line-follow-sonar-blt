#include <NewPing.h>
char data = 0;        //VARIABLE FOR STORING BLUETOOTH DATA
int LMF=4;            //LEFT MOTOR FORWARD 
int LMB=5;            //LEFT MOTOR BACK
int RMF=7;            //RIGHT MOTOR FORWARD
int RMB=6;            //RIGHT MOTOR BACK
int L=13;             //LEFT LINE FOLLOW SENSOR
int M=12;             //MIDDLE LINE FOLLOW SENSOR
int R=11;             //RIGHT LINE FOLLOW SENSOR
int trigPin = 9;      // trig pin of HC-SR04
int echoPin = 10;     // Echo pin of HC-SR04
int distance = 100;
int MAX_DISTANCE = 400;
int distanceR = 0;
int distanceL = 0;
NewPing sonar(trigPin, echoPin, MAX_DISTANCE); 

void setup() {
  
Serial.begin(9600);                //Sets the baud for serial data transmission 
pinMode(LMF,OUTPUT); 
pinMode(LMB,OUTPUT); 
pinMode(RMF,OUTPUT); 
pinMode(RMB,OUTPUT); 
pinMode(L,INPUT); 
pinMode(M,INPUT); 
pinMode(R,INPUT); 
pinMode(trigPin, OUTPUT);         // set trig pin as output
pinMode(echoPin, INPUT);          //set echo pin as input to capture reflected waves
}

void loop(){
  
  if(Serial.available() > 0)      // SEND DATA ONLY WHEN YOU RECEIVE DATA
{
   data = Serial.read();          //READ THE INCOMING DATA AND STORE INTO DATA 

      // INTERPRETATION OF BLUETOOTH ENTRY DATA

switch (data)
{
   case'F':{ FORWARD();
   }
   break;

   case 'L':{ LEFT();
   } 
   break;
 
   case 'R':{ RIGHT();
   }
   break;
   
   case 'S':{ STOP();
   }
   break;

   case 'B':{ BACK();
   }
   break;
}
}

if(!digitalRead(L)&&digitalRead(M)&&!digitalRead(R)){ FORWARD(); //010 GO FORWARD
}
if(digitalRead(L)&&!digitalRead(M)&&!digitalRead(R)){ LEFT(); //100 GO LEFT
}
if(!digitalRead(L)&&!digitalRead(M)&&digitalRead(R)){ RIGHT(); //001 GO RIGHT
}

 if (distance < 10)
  {
  BACK();
  delay(300);
  TURNLEFT();
  delay(650);
  distanceL = LOOKLEFT();
  delay(500);
  TURNRIGHT();
  delay(1350);
  distanceR = LOOKRIGHT();
  delay(500);
  TURNLEFT();
  delay(700);
  STOP();
  delay(500);
  
  if(distanceL>=distanceR)
  {
    LEFT();
    delay(700);
    FORWARD();
    delay(600);
    RIGHT();
    delay(700);
    FORWARD();
    delay(1000);
    RIGHT();
    delay(700);
    do { FORWARD();
    } 
    while (!digitalRead(L)&&!digitalRead(M)&&!digitalRead(R));
    LEFT();
    delay(800);
  }else
  {
   RIGHT();
    delay(700);
    FORWARD();
    delay(600);
    LEFT();
    delay(1000);
    FORWARD();
    delay(1000);
    LEFT();
    delay(1000);
    do { FORWARD();
    } 
    while (!digitalRead(L)&&!digitalRead(M)&&!digitalRead(R));
    RIGHT();
    delay(800);
  }
 }
 
 distance = readPing();
  }
  
int LOOKLEFT()
{ 
     digitalWrite(LMF,LOW);
     analogWrite(LMB,0);
     analogWrite(RMF,0);
     digitalWrite(RMB,LOW);
     int distance = readPing();
     delay(100);
     return distance;
}

int LOOKRIGHT()
{ 
    digitalWrite(LMF,LOW);
    analogWrite(LMB,0);
    analogWrite(RMF,0);
    digitalWrite(RMB,LOW);
    int distance = readPing();
    delay(100);
    return distance;
    delay(100);
}
    
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 400;
  }
  return cm;
} 
  
void FORWARD(){ // FORWARD
digitalWrite(LMF,LOW);
analogWrite(LMB,255);
analogWrite(RMF,255);
digitalWrite(RMB,HIGH);
}

void LEFT(){ // LEFT
digitalWrite(LMF,LOW);
analogWrite(LMB,0);
analogWrite(RMF,255);
digitalWrite(RMB,HIGH);
}

void RIGHT(){ // RIGHT
digitalWrite(LMF,LOW);
analogWrite(LMB,255);
analogWrite(RMF,0);
digitalWrite(RMB,HIGH);
}

void BACK(){ //BACK
digitalWrite(LMF,HIGH);
analogWrite(LMB,255);
analogWrite(RMF,255);
digitalWrite(RMB,LOW);
}

void STOP(){ //STOP
digitalWrite(LMF,LOW);
analogWrite(LMB,0);
analogWrite(RMF,0);
digitalWrite(RMB,LOW);
}
void TURNLEFT(){ //BOTH MOTORS MAKE A STOPPED TURN
digitalWrite(LMF,HIGH);
analogWrite(LMB,140);
analogWrite(RMF,140);
digitalWrite(RMB,HIGH);
}
void TURNRIGHT(){ //BOTH MOTORS MAKE A STOPPED TURN
digitalWrite(LMF,LOW);
analogWrite(LMB,140);
analogWrite(RMF,140);
digitalWrite(RMB,LOW);
}
