//
// Created by Matias Pierobon on 8/21/16.
//

#ifndef HANDRECOGNITION_IMAGE_H
#define HANDRECOGNITION_IMAGE_H

#include <opencv2/opencv.hpp>

class Image {
protected:
    cv::Mat * src;

public:
    Image();
    Image(cv::Mat * src);
    virtual ~Image();

    void setSrc(cv::Mat * src);
    cv::Mat * getSrc();

    Image * copy();

    void flip(int i=1);

    void cvtColor(int color);
    void inRange(cv::InputArray min, cv::InputArray max);
    void erode(cv::Size size, cv::Point anchor = cv::Point(-1, -1), int shape = cv::MORPH_RECT);
    void dilate(cv::Size size, cv::Point anchor = cv::Point(-1, -1), int shape = cv::MORPH_RECT);
    void getAvgColor( int avg[3] );
    void blur(cv::Size ksize, cv::Point anchor=cv::Point(-1,-1),
              int borderType=cv::BORDER_DEFAULT);
    void medianBlur(int size);
    std::vector<std::vector<cv::Point>> getContours();
    std::vector<cv::Point> getLargestContour();

    Image * roi(int x, int y, int w, int h);
};


#endif //HANDRECOGNITION_IMAGE_H
