/***************************************************************************/
// File			  [bluetooth.h]
// Author		  [Erik Kuo]
// Synopsis		[Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 2*/

#include<SoftwareSerial.h>
/*enum BT_CMD {
  NOTHING,
  stop_motion,
  go_foward,
  back_up,
  left_turn,
  right_turn
};*/

BT_CMD ask_BT(){
    BT_CMD message=NOTHING;
    char cmd;
    if(BT.available()){
      // TODO:
      // 1. get cmd from SoftwareSerial object: BT
      // 2. link bluetooth message to your own command type
       cmd = BT.read()
       if (cmd == 'f'){
           MotorWriting(150, 150);      }
      if (cmd == 'l'){
        MotorWriting(150, 100);
      }
      if (cmd == 'b'){
      MotorWriting(-100, -100)
      }
      if (incomingbyte == 'r'){
      MotorWriting(100, 150)
      }
      if (cmd == 's'){
       MotorWriting(0, 0);
      }
      
       
      #ifdef DEBUG
      Serial.print("cmd : ");
      Serial.println(cmd);
      #endif
    }
    return message;
}// ask_BT

// send msg back through SoftwareSerial object: BT
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg)
{if (digitalRead(l1) == HIGH)&& digitalRead(l2) == HIGH) &&digitalRead(l3) == HIGH)&&  digitalRead(r1) == HIGH)&&digitalRead(r2) == HIGH)&& digitalRead(r3) == HIGH)){ 
 BT.write("encounter_a_node")；}
         
              
}// send_msg

// send UID back through SoftwareSerial object: BT
void send_byte(byte *id, byte& idSize) {
  for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
    BT.write(id[i]);
  }
  #ifdef DEBUG
  Serial.print("Sent id: ");
  for (byte i = 0; i < idSize; i++) {  // Show UID consequently.
    Serial.print(id[i], HEX);
  }
  Serial.println();
  #endif
}// send_byte
