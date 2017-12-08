//SnakeSpinalCord - Version05
#include <Servo.h>

//SnakeSpinalCord04
//20171105 JPC started John Calder 05 Nov 2017
//20171201 JPC bring in servo testing and lose SoftwareSerial
//20171208 JPC edit and update comments
//         

//Robot snake has a smartphone or smartwatch "brain" in its head 
//The "body" has 10 segments. Each segment has 2 servos - 
//- one for vertical and one for horizontal movement.
//
//The "brain" sends serial commands by bluetooth.
//The "spinal cord" is an HC-05 unit receiving these commands 
//  and passing them on from its "TX" pin to 3 x Arduino Nano boards.
//  The HC-05 TX for a simplified first version connects to a single wire that runs the length of the robosnake
//  and is connected to pin RX of each Nano board.
//  Later versions will use an I2C bus line to make 2-way communication possible.
//  Each board recognises the signals with its prefix 'A', 'B' or 'C' and ignores the others.
//  Each Nano runs 6 or 8 servos on 3 or 4 segments using 5,6,7,8,9,10,11,12.
//  Pin 4 is SoftwareSerial loopback and monitoring.
//  Ports A0, A1 etc may be useful in future for hardware config eg switch into test mode.

//Serial command protocol by example: 
//  "A3-050"-- "Attention Nano 'A' - set servo number '3' to 'minus 50 degrees from mid position".
//  "D0+000" -- "Attention Nano 'D' - set servo number '0' to 'mid' position".

//Config for this board
byte thisBoardId = 'A'; //Board 'A', 'B' or 'C' - later versions may use I2C with slave id numbers.

// Config for servos - fine adjustment to "mid" position

Servo servosArray[7];
// Config for servos - fine adjustment to "mid" position
int offset[8] = {0,0,0,0,0,0,0,0};
// Config for servos - direction switch values 1 or -1
int dir[8] = {1,1,1,1,1,1,1,1};
bool isAssembling = false;
int servoNumber = 0; //0 to 7 - on pins 4 to 11

int posNeg = 1;
int signalPlace = 0;
int val;

void setup() {
    // HC-05 reconfig from 9600 to 38400
    Serial.begin(38400);
    //TESTING
    Serial.println("Reset initialise.");

    //Setup 7 servos
    for(int i = 0; i <= 7; i++) {
      servosArray[i].attach(i+4);
    }
}

void loop() {
     
    // Keep reading from HC-05 
    while (Serial.available()) {
      byte c = Serial.read();
      //TESTING - echo back for monitor
      //Serial.write(c);
   
      //listen for thisBoard
      if(!isAssembling) {
        if(c == thisBoardId) {
          isAssembling = true;
          signalPlace = 0;
          val = 0;
          Serial.write("recv A");
        //Test only character for time delay
        }else if(c == 'x') {
          delay(500);
        }
      }else if(isAssembling) {
        signalPlace = signalPlace + 1;
        assemble(c);
      }
    }
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
    }
  }else if(signalPlace == 3) {
    val = val + (c - 48) * 100;
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
  //TESTING version
  Serial.println();
  Serial.println("Received a recognisable value:");
  val = val * posNeg;
  Serial.println(val);
  //apply direction switch for each servo
  val = (val * dir[servoNumber]);
  if(val > 50)val = 50;
  if(val < -50) val = -50;
  val = val + 90 + offset[servoNumber];
  servosArray[servoNumber].write(val);
  
}

