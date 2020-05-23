/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on yout own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>

/*===========================import variable===========================*/
int extern r1, l1, r2, l2, r3, l3;
int extern _Tp;
/*===========================import variable===========================*/
// TODO: add some function to control your car when encounter a node
// here are something you can try: left_turn, right_turn... etc.
void left_turn(){
  MotorWriting(0, 0);
  delay(1000);
  MotorWriting(0, 90);
  delay(400);
  while(!(l2 && !r3 && !l3 && !r2 && !r1)){
    MotorWriting(0, 90);
    l1 = digitalRead(L1);
    l2 = digitalRead(L2);
    l3 = digitalRead(L3);
    r1 = digitalRead(R1);
    r2 = digitalRead(R2);
    r3 = digitalRead(R3);
      Serial.print("left");
  }
}
void right_turn(){
  MotorWriting(0, 0);
  delay(1000);
  MotorWriting(90, 0);
  delay(400);
  while(!((r1 ||r2) && !r3 && !l3 && !l2 && !l1)){
    MotorWriting(90, 0);
    l1 = digitalRead(L1);
    l2 = digitalRead(L2);
    l3 = digitalRead(L3);
    r1 = digitalRead(R1);
    r2 = digitalRead(R2);
    r3 = digitalRead(R3);
      Serial.print("right");
  }
  Serial.println("exit");
}
void u_turn(){
  MotorWriting(0, 0);
  delay(300);
  MotorWriting(80, -90);
  delay(600);
  while(!(r2 && !r3 && !l2 && !l2 && !l1)){
    MotorWriting(80, -90);
    l1 = digitalRead(L1);
    l2 = digitalRead(L2);
    l3 = digitalRead(L3);
    r1 = digitalRead(R1);
    r2 = digitalRead(R2);
    r3 = digitalRead(R3);
      Serial.print("right");
  }
}
void advance(){
  delay(1);
}
