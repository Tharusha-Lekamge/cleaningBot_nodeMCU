#include "relativeMapGen.h"

RelativeMapGen::RelativeMapGen(int (*relMapIn_arr)[11])
{
    this->relMap_arr = relMapIn_arr;
    this->sharpMountServo.attach(1);
}

bool RelativeMapGen::initArray(int (*relMapIn_arr)[11])
{
    this->relMap_arr = relMapIn_arr;
    return true;
}

bool RelativeMapGen::isInRange(float sharpReading, int blockVal)
{
    if (sharpReading >= blockVal - 5 && sharpReading <= blockVal + 5)
    {
        return true;
    }
    return false;
}

bool RelativeMapGen::checkForObstacle(int index)
{
    float distance = this->sharp.getDistance();
    // Serial.println(distance);
    if (isInRange(distance, this->dist[index]))
    {
        return (true);
    }
    return (false);
}

void RelativeMapGen::updateMap()
{
    // int distance;
    {
        Servo sharpMountServo1;
        sharpMountServo1.attach(1);
        for (int index = 0; index < 60; index++)
        {
            sharpMountServo1.write(angles[index]);
            // Serial.print(angles[index]);
            // Serial.print(" ");
            if (this->checkForObstacle(index))
            {
                relMap_arr[mapBlock[index][0]][mapBlock[index][1]] += 1;
            }
            delay(200);
        }
    }
}
