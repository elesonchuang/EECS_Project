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
 stop_motion(){
  MotorWriting(0,0)
 }
 go_foward(){
  MotorWriting(100,100)
 }
 back_up(){
  MotorWriting(-100,-100)
   }
 left_turn(){
  MotorWriting(100,-100)；
  delay(750)；
 }
 right_turn(){
  MotorWriting(-100,100)；
  delay(750)；
 }
 
      
