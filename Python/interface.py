import BT
import maze
import score

# hint: You may design additional functions to execute the input command, which will be helpful when debugging :)
    
class interface:
    def __init__(self):
        print("")
        print("Arduino Bluetooth Connect Program.")
        print("")
        self.ser = BT.bluetooth()
        port = input("PC bluetooth port name: ")
        while(not self.ser.do_connect(port)):
            if(port == "quit"):
                self.ser.disconnect()
                quit()
            port = input("PC bluetooth port name: ")
        input("Press enter to start.")
        self.ser.SerialWrite('s')

    def get_UID(self):
        return self.ser.SerialReadByte()

    def get_message(self):
        return self.ser.SerialReadString()
        
    def send_action(self,dirc):
        ADVANCE = 1
        U_TURN = 2
        TURN_RIGHT = 3
        TURN_LEFT = 4
        HALT = 5
        # TODO : send the action to car
        if (dirc == ADVANCE):
            self.ser.SerialWrite('f')
        elif(dirc == U_TURN): 
            self.ser.SerialWrite('b')
        elif(dirc == TURN_RIGHT):
            self.ser.SerialWrite('r')
        elif(dirc == TURN_LEFT):
            self.ser.SerialWrite('l')
        elif(dirc == HALT):
            self.ser.SerialWrite('s')

        return

    def end_process(self):
        self.ser.SerialWrite('e')
        self.ser.disconnect()


if __name__ == '__main__':
    test = interface()
    