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
/*===========================import variable===========================*/

// Write the voltage to motor.
void MotorWriting(double vL, double vR){
  if (vR >= 0){
    analogWrite(MotorL_PWML, vR);
    digitalWrite(MotorR_I1, HIGH);
    digitalWrite(MotorR_I2, LOW);
  }
  else if (vR < 0){
    analogWrite(MotorL_PWML, -vR);
    digitalWrite(MotorR_I1, LOW);
    digitalWrite(MotorR_I2, HIGH);
  }
  if (vL >= 0){
    analogWrite(MotorR_PWMR, vL);
    digitalWrite(MotorL_I3, HIGH);
    digitalWrite(MotorL_I4, LOW);
  }
  else if (vL < 0){
    analogWrite(MotorR_PWMR, -vL);
    digitalWrite(MotorL_I3, LOW);
    digitalWrite(MotorL_I4, HIGH);
  }
}// MotorWriting

// P/PID control Tracking
void tracking(int l1,int l2,int l3,int r3,int r2,int r1){
  //TODO: complete your P/PID tracking code
  
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
    /*
    if (cnt == 0){
      MotorWriting(-90, -90);//back the car when it is off the track
    }
    */
    if (ave_error >= 0.75){
      MotorWriting(-110, 110);//big left spin
    }
    else if (ave_error <= -0.75){
      MotorWriting(110, -110);//big right spin 
    }
    else if (ave_error >= 0.5){
      MotorWriting(-90, 90);//small left spin 
    }
    else if (ave_error <= -0.5){
      MotorWriting(90, -90);// small right spin 
    }
    else{
      MotorWriting(90, 90);// go forward
    }
  
}// tracking
