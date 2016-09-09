//
// Created by Matias Pierobon on 8/21/16.
//

#ifndef HANDRECOGNITION_ROI_H
#define HANDRECOGNITION_ROI_H


#include "Image.h"

class RoI : public Image {

private:
    cv::Point * p1;
    cv::Point * p2;
    Image * origin;

public:
    RoI();
    RoI(Image * img, cv::Point * p1, cv::Point * p2);
    RoI(Image * img, int x, int y, int w, int h);
    ~RoI();

    void setOrigin(Image * img);
    Image * getOrigin();

    void setUpperCorner(cv::Point * p);
    cv::Point * getUpperCorner();

    void setLowerCorner(cv::Point * p);
    cv::Point * getLowerCorner();

    void drawRect();
    void drawRect(Image * src, cv::Scalar color = cv::Scalar(0, 255, 0), int thickness = 1);

};


#endif //HANDRECOGNITION_ROI_H
