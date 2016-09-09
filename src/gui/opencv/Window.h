//
// Created by Matias Pierobon on 8/23/16.
//

#ifndef HANDRECOGNITION_WINDOW_H
#define HANDRECOGNITION_WINDOW_H

#include <string>
#include "opencv2/ml.hpp"
#include "../../recognition/Image.h"

class Window {
private:
    std::string name;

public:
    Window(const std::string &name);

    std::string getName();

    void show(const cv::Mat &img);
    void show(Image * img);
    void destroy();
};

#endif //HANDRECOGNITION_WINDOW_H
