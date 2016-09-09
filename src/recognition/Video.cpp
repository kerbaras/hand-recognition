//
// Created by Matias Pierobon on 8/21/16.
//

#include "Video.h"

Video::Video() {
    videoCapture = new cv::VideoCapture();
}

Video::Video(int cam) {
    videoCapture = new cv::VideoCapture(cam);
}

Video::Video(const std::string &filename) {
    videoCapture = new cv::VideoCapture(filename);
}

Image * Video::getFrame() {
    cv::Mat * frame = new cv::Mat();
    *videoCapture >> *frame;
    return new Image(frame);
}

bool Video::isOpened() {
    return this->videoCapture->isOpened();
}

void Video::setVideoCapture(cv::VideoCapture *videoCapture) {
    this->videoCapture = videoCapture;
}

cv::VideoCapture* Video::getVideoCapture() {
    return this->videoCapture;
}

Video::~Video() {
    delete this->videoCapture;
}