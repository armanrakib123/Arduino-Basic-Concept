#include <Servo.h>
Servo servo1;

// Servo position constants
#define SERVOMIN  30
#define SERVOMID  90
#define SERVOMAX  150
#define TurnLeft servo1.write(SERVOMIN)
#define TurnMid  servo1.write(SERVOMID)
#define TurnRight servo1.write(SERVOMAX)

// Motor pins
int motorA1 = 5;
int motorA2 = 6;
int ENA     = 3;   // ENA controls speed of Motor A (must be a PWM pin)
int motorB1 = 9;
int motorB2 = 10;

// Peripherals
int buzzer  = 4;
int light1  = 12;
int light2  = 13;
int light3  = 11;

// State variables
int state;
int vSpeed;
char ch;

void setup() {
  servo1.attach(2); // Attach servo to pin 2 (not 3, since ENA is on pin 3 now)
  
  // Set pin modes
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(ENA, OUTPUT);        // ENA added
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read serial data
  if (Serial.available() > 0) {
    state = Serial.read();
    ch = state;
  }

  // Speed selection (based on numeric characters)
  if (state >= '0' && state <= '9') {
    vSpeed = map(state, '0', '9', 0, 240);
  } else if (state == 'q') {
    vSpeed = 255;
  }

  // Movement commands
  if (state == 'F') {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    analogWrite(ENA, vSpeed);  // Enable Motor A with speed
    TurnMid;
  }
  else if (state == 'B') {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    analogWrite(ENA, vSpeed);
    TurnMid;
  }
  else if (state == 'R') {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    analogWrite(ENA, 0);
    TurnRight;
  }
  else if (state == 'L') {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    analogWrite(ENA, 0);
    TurnLeft;
  }
  else if (state == 'I') {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    analogWrite(ENA, vSpeed);
    TurnRight;
  }
  else if (state == 'G') {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    analogWrite(ENA, vSpeed);
    TurnLeft;
  }
  else if (state == 'J') {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    analogWrite(ENA, vSpeed);
    TurnRight;
  }
  else if (state == 'H') {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    analogWrite(ENA, vSpeed);
    TurnLeft;
  }
  else if (state == 'S') {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    analogWrite(ENA, 0);  // Stop Motor A
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }

  // Lights
  if (state == 'W') digitalWrite(light1, HIGH);
  if (state == 'w') digitalWrite(light1, LOW);
  if (state == 'U') digitalWrite(light2, HIGH);
  if (state == 'u') digitalWrite(light2, LOW);
  if (state == 'X') digitalWrite(light3, HIGH);
  if (state == 'x') digitalWrite(light3, LOW);

  // Buzzer
  if (state == 'V') tone(buzzer, 500);
  if (state == 'v') noTone(buzzer);
}
