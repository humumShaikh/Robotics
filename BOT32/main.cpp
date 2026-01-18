#include <Arduino.h>                  //include this file if you're working in platformIO
#include <BluetoothSerial.h>          //including the esp32 serial bluetooth library

BluetoothSerial SerialBT;             //object of class BluetoothSerial as SerialBT

int val;

#define enableA 2
#define enableB 26

#define m1A 5
#define m1B 4
#define m2A 13
#define m2B 27

#define buzzer 25 

#define RGB_R 12
#define RGB_G 23
#define RGB_B 14

#define servoPin 


void moveForward()                    //for the skoolbot / bot32 to move forward
{
  digitalWrite(enableA,HIGH);
  digitalWrite(enableB,HIGH);
  digitalWrite(m1A,HIGH);
  digitalWrite(m1B,LOW);
  digitalWrite(m2A,HIGH);
  digitalWrite(m2B,LOW);
}

void moveBackward()                  //for the skoolbot / bot32 to move backward
{
  digitalWrite(enableA,HIGH);
  digitalWrite(enableB,HIGH);
  digitalWrite(m1A,LOW);
  digitalWrite(m1B,HIGH);
  digitalWrite(m2A,LOW);
  digitalWrite(m2B,HIGH);
}

void moveLeft()                      //for the skoolbot / bot32 to rotate left
{
  digitalWrite(enableA,HIGH);
  digitalWrite(enableB,HIGH);
  digitalWrite(m1A,LOW);
  digitalWrite(m1B,HIGH);
  digitalWrite(m2A,HIGH);
  digitalWrite(m2B,LOW);
}

void moveRight()                      //for the skoolbot / bot32 to rotate right
{
  digitalWrite(enableA,HIGH);
  digitalWrite(enableB,HIGH);
  digitalWrite(m1A,HIGH);
  digitalWrite(m1B,LOW);
  digitalWrite(m2A,LOW);
  digitalWrite(m2B,HIGH);
}

void stop(){
  digitalWrite(enableA,LOW);
  digitalWrite(enableB,LOW);
  digitalWrite(m1A,LOW);
  digitalWrite(m1B,LOW);
  digitalWrite(m2A,LOW);
  digitalWrite(m2B,LOW);
}


void setup(){
  Serial.begin(115200);
  SerialBT.begin("BOT32");

  pinMode(enableA,OUTPUT);
  pinMode(enableB,OUTPUT);
  pinMode(m1A,OUTPUT);
  pinMode(m1B,OUTPUT);
  pinMode(m2A,OUTPUT);
  pinMode(m2B,OUTPUT);

  pinMode(buzzer,OUTPUT);

  pinMode(RGB_R,OUTPUT);
  pinMode(RGB_G,OUTPUT);
  pinMode(RGB_B,OUTPUT);
}

void loop(){

  while(SerialBT.available()==0){}    //wait until there's anything available on the bluetooth serial
  
  val = SerialBT.read();

  if(val==191){moveForward();}
  if(val==192){moveLeft();}
  if(val==193){moveRight();}
  if(val==194){moveBackward();}

  if(val==195){digitalWrite(RGB_R,HIGH);}
  if(val==196){digitalWrite(RGB_R,LOW);}

  if(val==197){digitalWrite(RGB_G,HIGH);}
  if(val==198){digitalWrite(RGB_G,LOW);}

  if(val==199){digitalWrite(RGB_B,HIGH);}
  if(val==200){digitalWrite(RGB_B,LOW);}

  if(val==201){digitalWrite(buzzer,HIGH);}
  if(val==202){digitalWrite(buzzer,LOW);}



}





