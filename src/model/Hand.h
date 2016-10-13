//
// Created by Matias Pierobon on 8/21/16.
//

#ifndef HANDRECOGNITION_HAND_H
#define HANDRECOGNITION_HAND_H

#include <vector>
#include "opencv2/ml.hpp"
#include "../recognition/Image.h"

class Hand {
private:
    cv::Point * center;
    std::vector<cv::Point> contour;
    std::vector<cv::Point> hull;
    std::vector<cv::Vec4i> defects;
    float distanceP2P(cv::Point a, cv::Point b);
    float getAngle(cv::Point s, cv::Point f, cv::Point e);

public:
    Hand();
    Hand(std::vector<cv::Point> contours);
    ~Hand();

    cv::Point * getCenter();
    std::vector<cv::Point> getContour();
    std::vector<cv::Point> getHull();
    std::vector<cv::Vec4i> getDefects();
    void draw(Image * image);

};


#endif //HANDRECOGNITION_HAND_H
