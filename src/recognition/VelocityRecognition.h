//
// Created by matias on 9/9/16.
//

#ifndef HANDRECOGNITION_VELOCITYRECOGNITION_H
#define HANDRECOGNITION_VELOCITYRECOGNITION_H


#include "../model/Hand.h"
#include "../model/Point.h"

class VelocityRecognition {

public:
    VelocityRecognition();
    void fromHand(Hand * hand, Point *center);
    int getMotor1();
    int getMotor2();
};


#endif //HANDRECOGNITION_VELOCITYRECOGNITION_H
