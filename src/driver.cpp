#include "driver.h"
#include "Arduino.h"

#include "driver.h"

void Driver::followPath(int *path)
{
    while (*path != -1)
    {
        switch (*path)
        {
        case FWD:
            forward();
            break;

        case LFT:
            left();
            break;

        case RGT:
            right();
            break;

        case BCK:
            left();
            left();
            break;
        default:
            break;
        }
        path++;
        delay(1000);
    }
}

void Driver::forward()
{
    Serial.println("FWD");
    digitalWrite(D0, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    delay(5000);
    stop();
}

void Driver::left()
{
    Serial.println("LFT");
    digitalWrite(D0, HIGH);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    delay(500);
    digitalWrite(D0, LOW);
}

void Driver::right()
{
    Serial.println("RHGT");
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    delay(500);
    digitalWrite(D2, LOW);
}

void Driver::stop()
{
    Serial.println("STOP");
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
}