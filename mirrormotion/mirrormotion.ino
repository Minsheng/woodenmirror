#include <Servo.h>
/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Connect LED from pin 11 through a resistor to ground 
For more information see http://learn.adafruit.com/photocells 

Wooden Mirror sketch created on Novemeber 7th, 2015

Iteration No.2 control 3 photoresistors + 3 servo motors (180 degree)
servo arrangement in a column
1 -> top
2 -> middle
3 -> bottom
*/

#define DEBUG 0

#define NUM_PR 3 // numbers of photoresistors
#define PR_THRESHOLD 900

#define SERVO_PIN_1 8
#define SERVO_PIN_2 9
#define SERVO_PIN_3 10

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

//int frame1PushedOut = 0;
//int frame2PushedOut = 0;
//int frame3PushedOut = 0;

int lastServoPos1 = INIT_POS;
int lastServoPos2 = INIT_POS;
int lastServoPos3 = INIT_POS;

Servo servo1;
Servo servo2;
Servo servo3;

/* better timing control */
int  updateInterval;      // interval between updates
unsigned long lastUpdate; // last update of position

class Slider
{
  Servo servo;              // the servo
  int pos;              // current servo position
  int lastPos;
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position
 
public: 
  Slider(int interval)
  {
    updateInterval = interval;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      servo.write(pos);
//      Serial.println(pos);
    }
  }
};

void setup(void) {
  Serial.begin(9600);
  
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);
  servo3.attach(SERVO_PIN_3);
  
  servo1.write(INIT_POS);
  servo2.write(INIT_POS);
  servo3.write(INIT_POS);
}

void loop(void) {
  if (DEBUG) {
    int prVal = 0;
    for (int j=0; j<NUM_PR; j++) {
      prVal = analogRead(j);
      Serial.print("Sensor ");
      Serial.print(j);
      Serial.print("is ");
      Serial.println(prVal);
    }
//    delay(10);
  } else {
    int prVal = 0;
    for (int i=0; i<NUM_PR; i++) {
      prVal = analogRead(i);
      
//      Serial.print("Sensor ");
//      Serial.print(i);
//      Serial.print("is ");
//      Serial.println(prVal);
      
      square_motion(i, prVal);
    }
  }
  delay(100);
}

void square_motion(int pr, int prVal) {
  int servoPos = compute_distance(prVal);
  switch (pr) {
    case 0:
      if (servoPos > lastServoPos1) {
        servo1.write(servoPos);
      } else {
        int updateInterval = 15;
        unsigned long lastUpdate;
        Serial.print("current time is ");
        Serial.println(millis());
        
        // if last servo position is further, slowly move back
        for (int i = lastServoPos1; i >= servoPos; i --) {
          if ((millis() - lastUpdate) > updateInterval) {
            lastUpdate = millis();
            Serial.print("last time is ");
            Serial.println(lastUpdate);
            if (i <= (lastServoPos1 - servoPos)*0.2) {
              updateInterval *= 0.8;
            }
            servo1.write(i);
          }
        }
      }
      
      lastServoPos1 = servoPos;
      break;
    case 1:
      if (servoPos > lastServoPos2) {
        servo2.write(servoPos);
      } else {
        int updateInterval = 10;
        unsigned long lastUpdate;
        // if last servo position is further, slowly move back
        for (int i = lastServoPos2; i >= servoPos; i --) {
          if ((millis() - lastUpdate) > updateInterval) {
            lastUpdate = millis();
            if (i <= (lastServoPos2 - servoPos)*0.2) {
              updateInterval *= 0.8;
            }
            servo2.write(i);
          }
        }
      }
      
      lastServoPos2 = servoPos;
      break;
    case 2:
      if (servoPos > lastServoPos3) {
        servo3.write(servoPos);
      } else {
        int updateInterval = 15;
        unsigned long lastUpdate;
        // if last servo position is further, slowly move back
        for (int i = lastServoPos3; i >= servoPos; i --) {
          if ((millis() - lastUpdate) > updateInterval) {
            lastUpdate = millis();
            if (i <= (lastServoPos3 - servoPos)*0.2) {
              updateInterval *= 0.8;
            }
            servo3.write(i);
          }
        }
      }
      
      lastServoPos3 = servoPos;
      break;
    default:
      break;
  }
}

int compute_distance(int prVal) {
  if (prVal > PR_THRESHOLD*0.8 && prVal <= PR_THRESHOLD) {
    return INIT_POS;
  } else if (prVal > PR_THRESHOLD*0.6 && prVal <= PR_THRESHOLD*0.8) {
    return PUSH_DIS_1;
  } else {
    return PUSH_DIS_3;
  }
}

