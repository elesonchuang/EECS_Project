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
  delay(300);
  MotorWriting(100, 100);
  delay(300);
  MotorWriting(0, 0);
  delay(300);
  while(!(!r1 && !r2 && (r3 || l3) && !l2 && !l1)){
    MotorWriting(-100, 100);
  }
  tracking(l1, l2, l3, r3, r2, r1);
}
void right_turn(){
  delay(300);
  MotorWriting(100, 100);
  delay(300);
  MotorWriting(0, 0);
  delay(300);
  while(!(!r1 && !r2 && (r3 || l3) && !l2 && !l1)){
    MotorWriting(100, -150);
  }
  tracking(l1, l2, l3, r3, r2, r1);
}
void u_turn(){
  MotorWriting(100, 100);
  delay(300);//still need modification.
  while(!(!r1 && !r2 && (r3 || l3) && !l2 && !l1)){
    MotorWriting(100, -100);
  }
  tracking(l1, l2, l3, r3, r2, r1);
}
void advance(){
  tracking(l1, l2, l3, r3, r2, r1);
  delay(200);
}
