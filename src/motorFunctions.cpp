#include <Arduino.h>

const uint8_t rightMotorPins[2] = {4, 5};
const uint8_t leftMotorPins[2] = {6, 7};

void setupMotors()
{
    pinMode(leftMotorPins[0], OUTPUT);
    pinMode(leftMotorPins[1], OUTPUT);
    pinMode(rightMotorPins[0], OUTPUT);
    pinMode(rightMotorPins[1], OUTPUT);
}

void stop()
{
    digitalWrite(leftMotorPins[0], 0);
    digitalWrite(leftMotorPins[1], 0);
    digitalWrite(rightMotorPins[0], 0);
    digitalWrite(rightMotorPins[1], 0);
}

void forward()
{
    digitalWrite(leftMotorPins[0], 0);
    digitalWrite(leftMotorPins[1], 1);
    digitalWrite(rightMotorPins[0], 0);
    digitalWrite(rightMotorPins[1], 1);
}

void left()
{
    digitalWrite(leftMotorPins[0], 1);
    digitalWrite(leftMotorPins[1], 0);
    digitalWrite(rightMotorPins[0], 0);
    digitalWrite(rightMotorPins[1], 1);
}

void right()
{
    digitalWrite(leftMotorPins[0], 0);
    digitalWrite(leftMotorPins[1], 1);
    digitalWrite(rightMotorPins[0], 1);
    digitalWrite(rightMotorPins[1], 0);
}

void driveForward(float speed)
{
    uint8_t pwm = UINT8_MAX * speed;
    digitalWrite(rightMotorPins[0], 0);
    analogWrite(rightMotorPins[1], pwm);
    analogWrite(leftMotorPins[0], UINT8_MAX - pwm);
    digitalWrite(leftMotorPins[1], 1);
}

void driveBackward(float speed)
{
    uint8_t pwm = UINT8_MAX * speed;
    digitalWrite(rightMotorPins[0], 1);
    analogWrite(rightMotorPins[1], UINT8_MAX - pwm);
    analogWrite(leftMotorPins[0], pwm);
    digitalWrite(leftMotorPins[1], 0);
}

void drive(float driveValue)
{
    if (driveValue == 0)
    {
        stop();
    }
    else if (driveValue > 0.0)
    {
        driveForward(abs(driveValue));
    }
    else
    {
        driveBackward(abs(driveValue));
    }
}