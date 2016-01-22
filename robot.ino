#include <Servo.h>
#include <NewPing.h>

const int PIN_LED = 13;
const int PIN_LEFT_ENGINE_1 = 2;
const int PIN_LEFT_ENGINE_2 = 3;
const int PIN_LEFT_ENGINE_SPEED = 6;
const int PIN_RIGHT_ENGINE_1 = 5;
const int PIN_RIGHT_ENGINE_2 = 4;
const int PIN_RIGHT_ENGINE_SPEED = 11;
const int ENGINE_SPEED = 254;

const int PIN_PING_TRIGGER = 19;
const int PIN_PING_ECHO = 18;
const int PING_MAX = 200;

const int PIN_SERVO = 10;

Servo myServo;
NewPing myPing(PIN_PING_TRIGGER, PIN_PING_ECHO, PING_MAX);

int distanceForward;
int distanceLeft;1
int distanceRight;

void setup() {
      pinMode(PIN_LED, OUTPUT);

      pinMode(PIN_LEFT_ENGINE_1, OUTPUT);
      pinMode(PIN_LEFT_ENGINE_2, OUTPUT);
      pinMode(PIN_LEFT_ENGINE_SPEED, OUTPUT);
      pinMode(PIN_RIGHT_ENGINE_1, OUTPUT);
      pinMode(PIN_RIGHT_ENGINE_2, OUTPUT);
      pinMode(PIN_RIGHT_ENGINE_SPEED, OUTPUT);

      myServo.attach(PIN_SERVO);
      myServo.write(90); // antal grader; 90 grader är rakt fram
}

void loop() {
      if (distanceForward > 0) {
            if (distanceForward < 25) {
                  stopEngine();

                  myServo.write(10);
                  delay(1000);
                  distanceLeft = pingMedelvarde();

                  myServo.write(170);
                  delay(1000);
                  distanceRight = pingMedelvarde();
                  myServo.write(90);

                  delay(1000);

                  if (distanceLeft < 25 && distanceRight < 25) {
                        reverse();
                        delay(1000);
                        if (random(2) == 0) {
                              turnLeft();
                        } else {
                              turnRight();
                        }
                  } else if (distanceLeft > distanceRight) {
                        turnLeft();
                        delay(1000);
                  } else if {
                        turnRight();
                        delay(1000);
                  }

                  digitalWrite(PIN_LED, LOW);
            }

            drive();
      }
}

void drive(void) {
      analogWrite(PIN_LEFT_ENGINE_SPEED, ENGINE_SPEED);
      digitalWrite(PIN_LEFT_ENGINE_1, LOW);
      digitalWrite(PIN_LEFT_ENGINE_2, HIGH);
      analogWrite(PIN_RIGHT_ENGINE_SPEED, ENGINE_SPEED);
      digitalWrite(PIN_RIGHT_ENGINE_1, LOW);
      digitalWrite(PIN_RIGHT_ENGINE_2, HIGH);
}

void reverse(void) {
      analogWrite(PIN_LEFT_ENGINE_SPEED, ENGINE_SPEED);
      digitalWrite(PIN_LEFT_ENGINE_1, HIGH);
      digitalWrite(PIN_LEFT_ENGINE_2, LOW);
      analogWrite(PIN_RIGHT_ENGINE_SPEED, ENGINE_SPEED);
      digitalWrite(PIN_RIGHT_ENGINE_1, HIGH);
      digitalWrite(PIN_RIGHT_ENGINE_2, LOW);
}

void stopEngine(void) {
      analogWrite(PIN_LEFT_ENGINE_SPEED, 0);
      digitalWrite(PIN_LEFT_ENGINE_1, LOW);
      digitalWrite(PIN_LEFT_ENGINE_2, LOW);
      analogWrite(PIN_RIGHT_ENGINE_SPEED, 0);
      digitalWrite(PIN_RIGHT_ENGINE_1, LOW);
      digitalWrite(PIN_RIGHT_ENGINE_2, LOW);
}

void turnLeft(void) {
      // Stop right engine
      analogWrite(PIN_RIGHT_ENGINE_SPEED, 0);

      // Start left engine
      analogWrite(PIN_LEFT_ENGINE_SPEED, ENGINE_SPEED);
      digitalWrite(PIN_LEFT_ENGINE_1, LOW);
      digitalWrite(PIN_LEFT_ENGINE_2, HIGH);
}

void turnRight(void) {
      // Stop left engine
      analogWrite(PIN_LEFT_ENGINE_SPEED, 0);

      // Start right engine
      analogWrite(PIN_RIGHT_ENGINE_SPEED, ENGINE_SPEED);
      digitalWrite(PIN_RIGHT_ENGINE_1, LOW);
      digitalWrite(PIN_RIGHT_ENGINE_2, HIGH);
}

int pingMedelvarde(void) {
      int total = 0;

      for (int i = 0; i < 5; i++) {
            total += myPing.ping_cm();
      }

      return total / 5;
}
