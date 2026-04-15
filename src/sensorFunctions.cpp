#include <Arduino.h>
#include <Servo.h>

#define FontServoPin 10
#define EchoPin 8
#define TrigPin 9

Servo frontServo = Servo();

void setupSensors()
{
    pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);
    frontServo.attach(FontServoPin);
    frontServo.write(90);
}

int getDistance()
{
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);

    long duration = pulseIn(EchoPin, HIGH);
    return (duration * .0343) / 2; // distance in centimeter
}

void getStatus(float threshold, bool* leftStatusAddress, bool* rightStatusAddress) {
  // left 
  frontServo.write(180); delay(1000);
  float leftDistance = getDistance();
  // right 
  frontServo.write(0); delay(1000);
  float rightDistance = getDistance();
  // reset position
  frontServo.write(90); delay(1000);

  *leftStatusAddress = leftDistance < threshold;
  *rightStatusAddress = rightDistance < threshold;
}
