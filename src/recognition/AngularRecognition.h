//
// Created by matias on 9/20/16.
//

#ifndef HANDRECOGNITION_ANGULARRECOGNITION_H
#define HANDRECOGNITION_ANGULARRECOGNITION_H

#include "VelocityRecognition.h"

class AngularRecognition : public VelocityRecognition {
public:
    AngularRecognition();
    virtual void fromHand(Hand * hand, Point *center);
};


#endif //HANDRECOGNITION_ANGULARRECOGNITION_H
