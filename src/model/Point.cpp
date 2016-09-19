//
// Created by Matias Pierobon on 8/21/16.
//

#include "Point.h"
#include <math.h>

Point::Point() {
    Point(0,0);
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

long double Point::distance(Point * p) {
    return sqrt(
            pow((double) (p->getX() - this->getX()), 2.0)
            +
            pow((double) (p->getY() - this->getY()), 2.0)
    );
}

int Point::getX() {
    return this->x;
}

void Point::setX(int x) {
    this->x = x;
}

int Point::getY() {
    return this->y;
}

void Point::setY(int y) {
    this->y = y;
}