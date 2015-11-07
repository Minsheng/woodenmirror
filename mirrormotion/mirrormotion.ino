#include <Servo.h>
/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Connect LED from pin 11 through a resistor to ground 
For more information see http://learn.adafruit.com/photocells 

Wooden Mirror sketch created on Novemeber 7th, 2015
*/


int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        // 

int pushedOut = 0;
int servo1Pin = 3;
Servo servo1;

void setup(void) {
  // We'll send debugging information via the Serial monitor
  pinMode(LEDpin, OUTPUT);
  servo1.attach(servo1Pin);
  servo1.write(180);
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
 
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
//  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
//  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  if (photocellReading >= 180) {
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

