//
// Created by matias on 9/20/16.
//

#include "AngularRecognition.h"

AngularRecognition::AngularRecognition() : VelocityRecognition::VelocityRecognition(){ }

void AngularRecognition::fromHand(Hand *hand, Point *center) {
    if(
      (hand->getCenter()->x == 0 && hand->getCenter()->y == 0) ||
      (hand->getDefects().size() < 3)
    ){
        this->motor1 = 0;
        this->motor2 = 0;
        return;
    }

    int x = hand->getCenter()->x - center->getX();
    int y = hand->getCenter()->y - center->getY();

    double theta = atan2(y, -x) + PI;

    int gap = center->getY()/5;

    cv::Point * pc;

    if(y > gap){
      pc = new cv::Point(x, y + hand->getRect().height/2);
    }

    long double radius = center->distance(hand->getCenter());

    int v = 0;

    if(radius > gap*3){
        v = 500;
    }else if(radius > gap*2){
        v = 400;
    }else if(radius > gap){
        v = 200;
    }


    if (theta >= 0 && theta < PI / 4) {
        this->motor1 = 2*v;
        this->motor2 = v*0.8;
    } else if (theta < 3 * PI / 4) {
        this->motor1 = v;
        this->motor2 = v;
    } else if (theta < 4 * PI / 4) {
        this->motor1 = v*0.8;
        this->motor2 = 2*v;
    } else if (theta < 5 * PI / 4) {
        this->motor1 = -v*0.8;
        this->motor2 = -2*v;
    } else if (theta < 7 * PI / 4) {
        this->motor1 = -v;
        this->motor2 = -v;
    } else {
        this->motor1 = -2*v;
        this->motor2 = -v*0.8;
    }
}
