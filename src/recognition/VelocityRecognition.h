//
// Created by matias on 9/9/16.
//

#ifndef HANDRECOGNITION_VELOCITYRECOGNITION_H
#define HANDRECOGNITION_VELOCITYRECOGNITION_H


#include "../model/Hand.h"
#include "../model/Point.h"


#define PI 3.14159265

class VelocityRecognition {
protected:
    int motor1;
    int motor2;

public:
    VelocityRecognition();
    int getMotor1();
    int getMotor2();
    virtual void fromHand(Hand * hand, Point *center);
};


#endif //HANDRECOGNITION_VELOCITYRECOGNITION_H
