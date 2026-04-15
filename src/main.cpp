#include <Arduino.h>
#include <Servo.h>
#include "motorFunctions.cpp"
#include "sensorFunctions.cpp"

#define DistanceThreshold 25.0F;

bool objectInFront = false;
bool objectInLeft = false;
bool objectInRight = false;

void setup()
{
    setupSensors();
    setupMotors();
    Serial.begin(9600);
}

// --- main loop ---
void loop()
{

    float distance = min(60.0, max(15.0, getDistance()));
    Serial.println(distance);

    if (distance < 25.0)
    {
        objectInFront = true;
    }

    if (!objectInFront)
    {
        driveForward(0.7);
    }
    else
    {
        stop();
        delay(500);
        getStatus(25.0, &objectInLeft, &objectInRight);

        // default left
        if (!objectInLeft)
        {
            left();
            delay(500);
            stop();
        }
        else if (!objectInRight)
        {
            right();
            delay(500);
            stop();
        }
        else
        {
            driveBackward(0.7);
            delay(500);
            stop();
        }

        objectInFront = false;
        objectInLeft = false;
        objectInRight = false;
    }

    delay(10);
}
