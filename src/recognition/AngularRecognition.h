//
// Created by matias on 9/20/16.
//

#ifndef HANDRECOGNITION_ANGULARRECOGNITION_H
#define HANDRECOGNITION_ANGULARRECOGNITION_H

#include "VelocityRecognition.h"

class AngularRecognition : public VelocityRecognition {
private:
    std::string descriptor;
public:
    AngularRecognition();
    virtual void fromHand(Hand * hand, Point *center);
    std::string getDescriptor();
};


#endif //HANDRECOGNITION_ANGULARRECOGNITION_H
