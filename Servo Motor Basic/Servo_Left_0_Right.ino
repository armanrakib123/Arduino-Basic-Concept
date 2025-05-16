#include <Servo.h>

Servo servo;  // create servo object to control a servo
int pos = 0;  // variable to store the servo position

void setup() {
  Serial.begin(9600);       // start serial communication
  Serial.setTimeout(100);   // reduce timeout for faster response
  servo.attach(11);         // attach servo to pin 11
}

void loop() {
  if (Serial.available()) {
    int angle = Serial.parseInt(); // read the number sent by app

    if (angle >= 0 && angle <= 180) {
      servo.write(angle); // move the servo
    }
    // No Serial print — silent mode
  }
}
