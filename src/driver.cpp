#include "driver.h"

void visitAdjacentNode(Node *fromNode, Node *toNode)
{
    // Check the direction of the toNode
    if (toNode == fromNode->back)
    {
        // Driver.moveBack()
    }
    if (toNode == fromNode->front)
    {
        // Driver.moveBack()
    }
    if (toNode == fromNode->left)
    {
        // Driver.moveBack()
    }
    if (toNode == fromNode->right)
    {
        // Driver.moveBack()
    }
}

Driver::Driver(int motor1_1, int motor1_2, int motor2_1, int motor2_2, int motor1_EN, int motor2_EN, int speed)
{
    this->LM_1 = motor1_1;
    this->LM_2 = motor1_2;
    this->LM_EN = motor1_EN;
    this->RM_1 = motor2_1;
    this->RM_2 = motor2_2;
    this->RM_EN = motor2_EN; // Right Motor enable;
    this->speed = speed;
    digitalWrite(LM_EN, speed);
    digitalWrite(RM_EN, speed);
}

void Driver::follow_path(int *path)
{
    // array terminator is -1;
    // assign a -1 at the end of path before passing it onto this function
    while (*path != -1)
    {
        switch (*path)
        {
        case FWD:
            Serial.println("Forward");
            forward();
            break;

        case LFT:
            Serial.println("leFT");
            left();
            break;

        case RGT:
            Serial.println("rGHT");
            right();
            break;

        case BCK:
            Serial.println("bACK");
            left();
            left();
            break;
        default:
            break;
        }
        path++;
    }
}

void Driver::forward()
{
    digitalWrite(LM_1, HIGH);
    digitalWrite(LM_2, LOW);
    digitalWrite(RM_1, HIGH);
    digitalWrite(RM_2, LOW);
    delay(this->time_fwd);
    stop();
}

void Driver::left()
{
    digitalWrite(LM_1, LOW);
    digitalWrite(LM_2, LOW);
    digitalWrite(RM_1, HIGH);
    digitalWrite(RM_2, LOW);
    delay(time_turn);
    stop();
}

void Driver::right()
{
    digitalWrite(LM_1, HIGH);
    digitalWrite(LM_2, LOW);
    digitalWrite(RM_1, LOW);
    digitalWrite(RM_2, LOW);
    delay(time_turn);
    stop();
}

void Driver::stop()
{
    digitalWrite(LM_1, LOW);
    digitalWrite(LM_2, LOW);
    digitalWrite(RM_1, LOW);
    digitalWrite(RM_2, LOW);
}
