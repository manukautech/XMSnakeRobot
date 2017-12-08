## sketch_SnakeSpinalCord04 ##
Work in progress as at 08 Dec 2017.
Code for Arduino Nano microcontrollers in use as the servo controllers, responding to control strings sent from a smart phone via bluetooth. TODO is the code for I2C connection between multiple nanos.  

Protocol is 6 bytes.
Variable signalPlace counts them from 0 to 5

Byte 0 - thisBoardId - 'A', 'B', or 'C' for which nano responds  
Byte 1 - servoNumber - range 0 to 7  
Byte 2 - posNeg - '+' or '-' 
Byte 3 - val hundreds  
Byte 4 - val tens  
Byte 5 - val units  

By example:
"A4+015" - Set servo number 4 in nano group A to + 15 degrees from centre position
"C1-040" - Set servo number 1 in nano group C to - 40 degrees from centre position

You do not need a snake robot to run this. Connect 1 or more servos for proof of concept.

<img src="https://github.com/manukautech/XMSnakeRobot/blob/master/CodeSpinalCordArduino/NanoTesting01_WS.JPG" width="500" />

