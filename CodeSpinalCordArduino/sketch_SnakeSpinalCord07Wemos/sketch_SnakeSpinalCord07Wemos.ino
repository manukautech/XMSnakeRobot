//SnakeSpinalCord - Version07Wemos is for Wemos trial as "C" in this snake robot
//Variations for 'A', 'B' and 'C' are coded in. 
//Edit the const byte THIS_BOARD line below before uploading.
#include <Servo.h>

//20171223 JPC use of ReceiveOnlySoftwareSerial by Nick Gammon on "A" to receive signals from "B" and "C"
//Ref: http://gammon.com.au/Arduino/ReceiveOnlySoftwareSerial.zip
//#include <ReceiveOnlySoftwareSerial.h>

const byte THIS_BOARD = 'C';
String thisBoardId; // assigned to "A", "B" or "C" below

//ReceiveOnlySoftwareSerial softSerialB(10); // RX only
//ReceiveOnlySoftwareSerial softSerialC(11); // RX only

//20171105 JPC started John Calder 05 Nov 2017
//20171201 JPC bring in servo testing and lose SoftwareSerial
//20171208 JPC edit and update comments
//20171221 JPC begin testing on completed snake robot hardware
//20171223 JPC lose i2c and bring back SoftwareSerial       

//Robot snake has a smartphone or smartwatch "brain" in its head 
//The "body" has 10 segments. Each segment has 2 servos - 
//- one for vertical and one for horizontal movement.
//
//The "brain" sends serial commands by bluetooth.
//  The "spinal cord" is an HC-05 unit receiving these commands 
//  and passing them on from its "TX" pin to the "RX" pins of 3 x Arduino Nano.
//  each Nano receives all signals but can identify the first byte 'A' 'B' or 'C' and act on its signals only
//  'A' has the serial line to send back responses by Bluetooth.
//  'B' and 'C' send responses to 'A' which receives by SoftwareSerial then passes on to Bluetooth

//Serial command protocol by example: 
//  "A3-050"-- "Attention Nano 'A' - set servo number '3' to 'minus 50 degrees from mid position".
//  "C0+000" -- "Attention Nano 'C' - set servo number '0' to 'mid' position".

// Config for servos - fine adjustment to "mid" position

Servo servosArray[8];
// Default Config for servos - fine adjustment to "mid" position - see configA(), configB(), configC() below
int offset[8] = {0,0,0,0,0,0,0,0};
// Config for servos - direction switch values 1 or -1
int dir[8] = {1,1,1,1,1,1,1,1};
//Wemos special
int pinArray[8] = {D1, D2, D3, D4, D5, D6, D7, D8};
// Wemos lower level poss allow integrate later
// Ref: https://github.com/esp8266/Arduino/blob/master/variants/d1_mini/pins_arduino.h#L49-L61
// int pinArray[8] = {5, 4, 0, 2, 14, 12, 13, 15};

bool isAssembling = false;
int servoNumber = 0; //0 to 7 - on pins 4 to 11

int posNeg = 1;
int signalPlace = 0;
int val = 0;
bool isStartupTesting = true;
int nServos = 6; //default for A and B. C has 8 see config below
int pinOffset = 4; //default for Arduino Nano use pins 4,5,6 ...

//The code in configA(), configB(), config(C) needs custom editing for each snake robot
//with values from test results. Example values here are from snake "Harald" as at Dec 2017.
void configA() {
  thisBoardId = "A";
  offset[0] = 5;  dir[0] = 1;
  offset[1] = -5;  dir[1] = -1;
  //20171226 JPC change from 15 to 0
  offset[2] = 0;  dir[2] = -1;
  offset[3] = -15;  dir[3] = 1;
  offset[4] = 0;  dir[4] = 1;
  offset[5] = 25;  dir[5] = -1;
  offset[6] = 0;  dir[6] = 1;
  offset[7] = 0;  dir[7] = 1;
}

void configB() {
  thisBoardId = "B";
  offset[0] = -5;  dir[0] = 1;
  offset[1] = 0;  dir[1] = 1;
  offset[2] = -10;  dir[2] = 1;
  offset[3] = 25;  dir[3] = -1;
  offset[4] = -5;  dir[4] = 1;
  offset[5] = 0;  dir[5] = 1;
  offset[6] = 0;  dir[6] = 1;
  offset[7] = 0;  dir[7] = 1;
}

void configC() {
  thisBoardId = "C";
  nServos = 8;
  offset[0] = -30;  dir[0] = 1;
  offset[1] = -20;  dir[1] = 1;
  offset[2] = 20;  dir[2] = -1;
  offset[3] = 30;  dir[3] = -1;
  //20171226 JPC correction 20 to -20
  offset[4] = -20;  dir[4] = 1;
  offset[5] = -25;  dir[5] = 1;
  offset[6] = 0;  dir[6] = 1;
  offset[7] = 17;  dir[7] = -1;
}


void setup() {
    // HC-05 is reconfigured from 9600 to 38400
    Serial.begin(38400);
    //TESTING
    Serial.println("Startup " + thisBoardId);

    //config by THIS_BOARD
    if(THIS_BOARD == 'A') {
      configA();
      //softSerialB.begin(38400);
      //softSerialC.begin(38400);
    }else if(THIS_BOARD == 'B') {
      configB();
    }else if(THIS_BOARD == 'C') {
      configC();
    } else {
      Serial.println("ERROR: invalid Board Id");
      //TODO solder on coloured LEDS for cases like this
    }

    //Setup 6 or 8 servos
    for(int i = 0; i < nServos; i++) {
      servosArray[i].attach(pinArray[i]);
    }
    // Apply offset settings
    for(int i = 0; i < nServos; i++) {
      servosArray[i].write((offset[i] * dir[i]) + 90);
    } 

    // test on startup by flashing light pattern.
    //pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    //On Startup or Reset run a 3-flash-then-pause indication twice
//    if(isStartupTesting) {
//      flashTest(); flashTest();
//      isStartupTesting = false;
//    } 
    
    // Keep reading from HC-05
    while (Serial.available()) {
      byte c = Serial.read();
      //TESTING - echo back for monitor
      //Serial.write(c);
   
      //listen for 'A', 'B', or 'C'
      if(c == THIS_BOARD) {
        isAssembling = true;
        signalPlace = 0;
        val = 0;
        Serial.println("recv " + thisBoardId );
      }else if(c == 'x') {
        //character for time delay
        delay(500);
      }else if(isAssembling) {
        signalPlace += 1;
        assemble(c);
      }
    }

    //'A' relays responses from 'B' and 'C'
//    if(THIS_BOARD == 'A') {
//        if (softSerialB.available()) {
//          Serial.write(softSerialB.read());
//        }
//        if (softSerialC.available()) {
//          Serial.write(softSerialC.read());
//        }
//    }
}

void assemble(byte c) {
  if(signalPlace == 1) {
    servoNumber = c - 48;
  }else if(signalPlace == 2) {
    if(c == '-') {
      posNeg = -1;
    }else if(c == '+') {
      posNeg = 1;
    }else {
      //error condition, stop processing and if debugging send a signal
      isAssembling = false;
      Serial.println("ERROR - character 2 needs to be + or - ");
      return;
    }
  }else if(signalPlace == 3) {
    val = (c - 48) * 100;
  }else if(signalPlace == 4) {
    val = val + (c - 48) * 10;
  }else if(signalPlace == 5) {
    val = val + (c - 48);
    process();
    //return to listening mode
    isAssembling = false;
  }
}

void process() {
  val = val * posNeg;
  if(val > 50)val = 50;
  if(val < -50) val = -50;
  Serial.println("work value: " + val); 
  //apply direction switch for each servo
  val = (val + offset[servoNumber]) * dir[servoNumber];
  val = val + 90 ;
  servosArray[servoNumber].write(val);
}

//void flashTest() {
//  //only for initial setup - we see 3 flashes then a pause
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(300);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(300);
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(300);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(300);
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(300);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(3000);
//}

