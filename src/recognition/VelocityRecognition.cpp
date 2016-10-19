//
// Created by matias on 9/9/16.
//

#include "VelocityRecognition.h"

VelocityRecognition::VelocityRecognition() {
    this->motor1 = 0;
    this->motor2 = 0;
}

int VelocityRecognition::getMotor1() {
    return this->motor1;
}

int VelocityRecognition::getMotor2() {
    return this->motor2;
}

void VelocityRecognition::fromHand(Hand *hand, Point *center) { }
