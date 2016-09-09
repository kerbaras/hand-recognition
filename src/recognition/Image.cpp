//
// Created by Matias Pierobon on 8/21/16.
//

#include "Image.h"
#include "RoI.h"

Image::Image() {
    this->src = new cv::Mat();
}

Image::Image(cv::Mat *src) {
    this->src = src;
}

Image::~Image() {
    delete this->src;
}

Image* Image::copy() {
    cv::Mat * cp = new cv::Mat();
    this->src->copyTo(*cp);
    return new Image(cp);
}

void Image::cvtColor(int color) {
    cv::cvtColor(*this->src, *this->src, color);
}

void Image::flip(int i) {
    cv::flip(*src, *src, i);
}

void Image::inRange(cv::InputArray min, cv::InputArray max) {
    cv::inRange(*this->src, min, max, *this->src);
}

void Image::dilate(cv::Size size, cv::Point anchor, int shape) {
    cv::Mat kernel = cv::getStructuringElement(shape, size, anchor);
    cv::dilate(*this->src, *this->src, kernel, anchor);
}

void Image::erode(cv::Size size, cv::Point anchor, int shape) {
    cv::Mat kernel = cv::getStructuringElement(shape, size, anchor);
    cv::erode(*this->src, *this->src, kernel, anchor);
}

int getMedian(std::vector<int> val){
    int median;

    size_t size = val.size();

    std::sort(val.begin(), val.end());
    if (size  % 2 == 0)  {
        median = val[size / 2 - 1] ;
    } else{
        median = val[size / 2];
    }
    return median;
}

void Image::getAvgColor(int avg[3]) {
    Image * cp = this->copy();

    cv::Mat r = *(cp->getSrc());

    std::vector<int> hm;
    std::vector<int> sm;
    std::vector<int> lm;

    // generate vectors
    for(int i=2; i<r.rows-2; i++){
        for(int j=2; j<r.cols-2; j++){
            hm.push_back(r.data[r.channels()*(r.cols*i + j) + 0]) ;
            sm.push_back(r.data[r.channels()*(r.cols*i + j) + 1]) ;
            lm.push_back(r.data[r.channels()*(r.cols*i + j) + 2]) ;
        }
    }

    avg[0]=getMedian(hm);
    avg[1]=getMedian(sm);
    avg[2]=getMedian(lm);
    delete cp;
}

void Image::blur(cv::Size size, cv::Point anchor, int type) {
    cv::blur(*src, *src, size, anchor, type);
}

void Image::medianBlur(int size) {
    cv::medianBlur(*src, *src, size);
}

std::vector<std::vector<cv::Point>> Image::getContours() {
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat copy;
    src->copyTo(copy);
    cv::findContours(copy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    return contours;
}

std::vector<cv::Point> Image::getLargestContour() {
    std::vector<std::vector<cv::Point>> contours = this->getContours();

    int biggestContour=-1;
    double biggestArea = 0;

    for (int i = 0; i < contours.size(); i++){
        double area = cv::contourArea(contours[i]);
        if(cv::contourArea(contours[i]) > biggestArea){
            biggestArea = area;
            biggestContour = i;
        }
    }
    if(biggestContour==-1)
        return std::vector<cv::Point>(0);
    return contours[biggestContour];
}

void Image::setSrc(cv::Mat *src) {
    this->src = src;
}

Image* Image::roi(int x, int y, int w, int h) {
    return new RoI(this, x, y, w, h);
}

cv::Mat* Image::getSrc() {
    return this->src;
}
