//
// Created by Matias Pierobon on 8/21/16.
//

#include "RoI.h"

RoI::RoI() : Image::Image() {

}

RoI::RoI(Image *img, cv::Point *p1, cv::Point *p2) {
    this->origin = img;
    this->p1 = p1;
    this->p2 = p2;
    cv::Mat * src = new cv::Mat();
    *src = img->getSrc()->operator() (cv::Rect(p1->x, p1->y, p2->x - p1->x, p2->y - p1->y));
    this->src = src;

}

RoI::RoI(Image *img, int x, int y, int w, int h) {
    this->origin = img;
    cv::Mat * src = new cv::Mat();
    *src = img->getSrc()->operator() (cv::Rect(x, y, w, h));
    this->src = src;
    this->p1 = new cv::Point(x, y);
    this->p2 = new cv::Point(x + w, y + h);
}

void RoI::drawRect(Image *src, cv::Scalar color, int thickness) {
    cv::rectangle( *src->getSrc(), *p1, *p2, color, thickness );
}

void RoI::drawRect() {
    this->drawRect(this->origin);
}

void RoI::setOrigin(Image *img) {
    this->origin = img;
}

Image * RoI::getOrigin() {
    return this->origin;
}

void RoI::setUpperCorner(cv::Point * p) {
    this->p1 = p;
}

cv::Point * RoI::getUpperCorner() {
    return this->p1;
}

void RoI::setLowerCorner(cv::Point * p) {
    this->p2 = p;
}

cv::Point * RoI::getLowerCorner() {
    return this->p2;
}

RoI::~RoI() {
    delete this->p1;
    delete this->p2;
}