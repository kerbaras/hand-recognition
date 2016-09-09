//
// Created by Matias Pierobon on 8/21/16.
//

#ifndef HANDRECOGNITION_VIDEO_H
#define HANDRECOGNITION_VIDEO_H


#include "opencv2/highgui.hpp"
#include "Image.h"

class Video {

private:
    cv::VideoCapture * videoCapture;

public:
    Video();
    Video(int cam);
    Video(const std::string &filename);
    ~Video();

    void setVideoCapture(cv::VideoCapture * videoCapture);
    cv::VideoCapture * getVideoCapture();

    Image * getFrame();

    bool isOpened();
};


#endif //HANDRECOGNITION_VIDEO_H
