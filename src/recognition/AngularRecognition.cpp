//
// Created by matias on 9/20/16.
//

#include "AngularRecognition.h"

AngularRecognition::AngularRecognition() : VelocityRecognition::VelocityRecognition(){ }

void AngularRecognition::fromHand(Hand *hand, Point *center) {
    this->descriptor = "stop";
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
    pc = new cv::Point(hand->getCenter()->x, hand->getRect().tl().y);
    //if(y > 3*gap)
        //pc = new cv::Point(hand->getCenter()->x, hand->getRect().br().y);

    long double radius = center->distance(pc);
    delete pc;
    int v = 0,  vf=0;

    if(radius > gap*3){
        v = 500;
        vf = 3;
    }else if(radius > gap*2){
        v = 400;
        vf = 2;
    }else if(radius > gap){
        v = 200;
        vf= 1;
    }

    char d, s;
    if (theta >= 0 && theta < PI / 4) {
        this->motor1 = 2*v;
        this->motor2 = v*0.8;
        d = char('r');
        s = char('t');
    } else if (theta < 3 * PI / 4) {
        this->motor1 = v;
        this->motor2 = v;
        d = char('f');
        s = char('t');
    } else if (theta < 4 * PI / 4) {
        this->motor1 = v*0.8;
        this->motor2 = 2*v;
        d = char('l');
        s = char('t');
    } else if (theta < 5 * PI / 4) {
        this->motor1 = -v*0.8;
        this->motor2 = -2*v;
        d = char('l');
        s = char('b');
    } else if (theta < 7 * PI / 4) {
        this->motor1 = -v;
        this->motor2 = -v;
        d = char('b');
        s = char('b');
    } else {
        this->motor1 = -2*v;
        this->motor2 = -v*0.8;
        d = char('r');
        s = char('b');
    }
    if(vf > 0) {
        this->descriptor = "";
        this->descriptor += s;
        this->descriptor += d;
        this->descriptor += "_";
        this->descriptor += vf;
    }
}

std::string AngularRecognition::getDescriptor() {
    return this->descriptor;
}