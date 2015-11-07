#include <Servo.h>
/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Connect LED from pin 11 through a resistor to ground 
For more information see http://learn.adafruit.com/photocells 

Wooden Mirror sketch created on Novemeber 7th, 2015

Iteration No.1 control 4 photoresistors + 4 servo motors (180 degree)
servo arrangement (facing the front of the frames) 
1 -> top left
2 -> top right
3 -> bottom left
4 -> bottom right
*/
#define NUM_PR 4 // numbers of photoresistors
#define PR_THRESHOLD 180

#define SERVO_PIN_1 8
#define SERVO_PIN_2 9
#define SERVO_PIN_3 10
#define SERVO_PIN_4 11

/* push distance is rated by the proximity between the person and the frame 
0 -> initial position,
1 -> close
2 -> regular
3 -> far
*/
#define INIT_POS 0
#define PUSH_DIS_1 60
#define PUSH_DIS_2 120
#define PUSH_DIS_3 180

int PR_VAL_1;
int PR_VAL_2;
int PR_VAL_3;
int PR_VAL_4;

int frame1PushedOut = 0;
int frame2PushedOut = 0;
int frame3PushedOut = 0;
int frame4PushedOut = 0;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup(void) {
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
  servo4.attach(SERVO_PIN_4);
  
  servo1.write(INIT_POS);
  servo2.write(INIT_POS);
  servo3.write(INIT_POS);
  servo4.write(INIT_POS);
  
  Serial.begin(9600);   
}
 
void loop(void) {
  int prVal = 0;
  
  for (int i=0; i<4; i++) {
    prVal = analogRead(i);
    
    Serial.print("Analog reading = ");
    Serial.println(prVal);

    if (prVal >= PR_THRESHOLD) {
      if (!pushedOut) {
        pushedOut = 1;
        digitalWrite(LEDpin, HIGH);
        goIn();
      }
    } else {
      if (pushedOut) {
        pushedOut = 0;
        digitalWrite(LEDpin, LOW);
        goOut();
      }
    }
  
    switch i {
      case 0:
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      default:
        break;
    }
  }
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
//  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
//  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  
  
  delay(100);
}

void goIn() {
  servo1.write(180);
}

void goOut() {
  for (int i = 180; i >= 0; i --) {
       servo1.write(i);
       delay(5);
  }
}

