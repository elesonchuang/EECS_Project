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
enum BT_CMD {
  NOTHING = 0,
  // TODO: add your own command type here
  ADVANCE = 1,
  U_TURN = 2,
  TURN_RIGHT = 3,
  TURN_LEFT = 4,
  HALT = 5,
};

BT_CMD ask_BT(){
    BT_CMD message=NOTHING;
    char cmd;
    if(BT.available()){
      // TODO:
      // 1. get cmd from SoftwareSerial object: BT
      // 2. link bluetooth message to your own command type
      cmd = BT.read();
      if (cmd == 'f'){
        message = ADVANCE;
      }
      else if (cmd == 'b'){
        message = U_TURN;
      }
      else if (cmd == 'r'){
        message = TURN_RIGHT;
      }
      else if (cmd == 'l'){
        message = TURN_LEFT;
      }
      else if (cmd == 'h'){
        message = HALT;
      }
      #ifdef DEBUG
      Serial.print("cmd : ");
      Serial.println(cmd);
      Serial.println("dao1");
      Serial.println(message);
      Serial.println("dao2");
      #endif
    }
    return message;
}// ask_BT

// send msg back through SoftwareSerial object: BT
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg)
{
     // TODO:
     BT.write(msg);
     //Serial.println("I successfully sent message: ");
     Serial.println(msg);
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
