//
// Created by Matias Pierobon on 8/21/16.
//

#ifndef HANDRECOGNITION_HANDRECOGNITION_H
#define HANDRECOGNITION_HANDRECOGNITION_H


#include "../model/Hand.h"
#include "Video.h"

class HandRecognition {
private:
    std::string name;
    void createTrackbars(int track[], const std::string &name);
    int tracks[7][6];


public:
    HandRecognition(const std::string &name);
    void waitForHand(Video * video);
    Hand * getHand(Image * original);
};


#endif //HANDRECOGNITION_HANDRECOGNITION_H
