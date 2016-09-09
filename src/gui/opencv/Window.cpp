//
// Created by Matias Pierobon on 8/23/16.
//

#include "Window.h"

Window::Window(const std::string &name) {
    this->name = name;
    cv::namedWindow(name);
}

void Window::show(const cv::Mat &img) {
    cv::imshow(this->name, img);
}

void Window::show(Image *img) {
    this->show(*img->getSrc());
}

void Window::destroy() {
    cv::destroyWindow(this->name);
}

std::string Window::getName() {
    return this->name;
}