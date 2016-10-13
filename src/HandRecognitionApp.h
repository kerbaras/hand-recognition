//
// Created by Matias Pierobon on 8/21/16.
//

#ifndef HANDRECOGNITION_HANDRECOGNITIONAPP_H
#define HANDRECOGNITION_HANDRECOGNITIONAPP_H

#include "recognition/Image.h"
#include "model/Hand.h"

class HandRecognitionApp {
private:
    void buildGUI( Image * image, Hand * hand);
public:
    HandRecognitionApp();
};


#endif //HANDRECOGNITION_HANDRECOGNITIONAPP_H
