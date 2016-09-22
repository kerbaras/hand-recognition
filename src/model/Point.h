//
// Created by Matias Pierobon on 8/21/16.
//

#ifndef HANDRECOGNITION_POINT_H
#define HANDRECOGNITION_POINT_H


#include <opencv2/core/types.hpp>

class Point {
private:
    int x;
    int y;

public:
    Point();
    Point(int x, int y);

    int getX();
    void setX(int x);

    int getY();
    void setY(int y);

    long double distance(cv::Point * p);

};


#endif //HANDRECOGNITION_POINT_H
