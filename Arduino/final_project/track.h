/***************************************************************************/
// File			  [track.h]
// Author		  [Erik Kuo]
// Synopsis		[Code used for tracking]
// Functions  [MotorWriting, tracking]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>

/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/

/*===========================import variable===========================*/
int extern _Tp;
int extern r1, l1, r2, l2, r3, l3;
/*===========================import variable===========================*/

// Write the voltage to motor.
void MotorWriting(double vR, double vL){
  if (vR >= 0){
    analogWrite(MotorL_ENA, vR);
    digitalWrite(MotorR_I1, HIGH);
    digitalWrite(MotorR_I2, LOW);
  }
  else if (vR < 0){
    analogWrite(MotorL_ENA, -vR);
    digitalWrite(MotorR_I1, LOW);
    digitalWrite(MotorR_I2, HIGH);
  }
  if (vL >= 0){
    analogWrite(MotorR_ENB, vL);
    digitalWrite(MotorL_I3, HIGH);
    digitalWrite(MotorL_I4, LOW);
  }
  else if (vL < 0){
    analogWrite(MotorR_ENB, -vL);
    digitalWrite(MotorL_I3, LOW);
    digitalWrite(MotorL_I4, HIGH);
  }
}


bool all_high(){
  if (digitalRead(l1) == HIGH && digitalRead(l2) == HIGH && digitalRead(l3) == HIGH && digitalRead(r1) == HIGH && digitalRead(r2) == HIGH && digitalRead(r3) == HIGH){
    return true;
  }
  else return false;
}
bool all_low(){
  if (digitalRead(l1) != HIGH && digitalRead(l2) != HIGH && digitalRead(l3) != HIGH && digitalRead(r1) != HIGH && digitalRead(r2) != HIGH && digitalRead(r3) != HIGH){
    return true;
  }
  else return false;
}
bool at_center(){
  if (digitalRead(l1) == LOW && digitalRead(l2) == LOW && digitalRead(r1) == LOW && digitalRead(r2) == LOW && (digitalRead(r3) == HIGH or digitalRead(l3) == HIGH)){
    return true;
  }
  else return false;
}
void tracking(){
  while(BT.available() == 0){
            //IR module
            double ave_error = 0;
            double e[6] = {800, 800, 800, 800, 800, 800};
            int cnt = 0;
            if (digitalRead(l1) == HIGH) e[0] = 1;
            if (digitalRead(l2) == HIGH) e[1] = 0.5;
            if (digitalRead(l3) == HIGH) e[2] = 0; 
            if (digitalRead(r1) == HIGH) e[5] = -1;
            if (digitalRead(r2) == HIGH) e[4] = -0.5;
            if (digitalRead(r3) == HIGH) e[3] = 0; 
            for(int i = 0; i < 6; i++){
              if (e[i] < 800){
                cnt++;
                ave_error += e[i];
              }
            }
            
            if(cnt == 0){
              ave_error = 0;
            }
            else{
              ave_error /= cnt;
            }
            if (cnt == 0){
              MotorWriting(-100, -100);//back the car when it is off the track
            }
            else if (all_high()){
              MotorWriting(0, 0);
            }
            else if (ave_error >= 0.75){
              MotorWriting(130, -90);//big left spin
            }
            else if (ave_error <= -0.75){
              MotorWriting(-90, 130);//big right spin 
            }
            else if (ave_error >= 0.5){
              MotorWriting(115, -90);//small left spin 
            }
            else if (ave_error <= -0.5){
              MotorWriting(-90, 115);// small right spin 
            }
            else{
              MotorWriting(120, 100);// go forward
            }
          }
}

          
