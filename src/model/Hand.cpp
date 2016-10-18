//
// Created by Matias Pierobon on 8/21/16.
//

#include "Hand.h"
#include <opencv2/opencv.hpp>
#include <math.h>

Hand::Hand() {
    this->center = new cv::Point(0,0);
}

Hand::Hand(std::vector<cv::Point> contour) {
    this->contour = contour;

    double x = 0;
    double y = 0;
    if(contour.size() > 0){
        cv::Moments moments = cv::moments(contour);
        x = moments.m10/moments.m00;
        y = moments.m01/moments.m00;

        std::vector<int> hullI;
        cv::convexHull( cv::Mat(contour), this->hull, false );
        cv::convexHull( cv::Mat(contour), hullI, false );

        cv::convexityDefects(this->contour, hullI, this->defects);
        cv::Rect rect = cv::boundingRect(contour);

        std::vector<cv::Vec4i> newDefects;
        int startidx, endidx, faridx;
		    int tolerance =  rect.height/5;
		    float angleTol=95;

        for(int i=0; i < defects.size(); i++){
            cv::Vec4i v = defects[i];
      			startidx=v[0]; cv::Point ptStart(contour[startidx] );
      			endidx=v[1]; cv::Point ptEnd(contour[endidx] );
      			faridx=v[2]; cv::Point ptFar(contour[faridx] );
      			if(
                distanceP2P(ptStart, ptFar) > tolerance &&
                distanceP2P(ptEnd, ptFar) > tolerance &&
                getAngle(ptStart, ptFar, ptEnd  ) < angleTol
            ){
        				if( ptEnd.y > (rect.y + rect.height - rect.height/4 ) ){
        				}else if( ptStart.y > (rect.y + rect.height - rect.height/4 ) ){
        				}else {
          					newDefects.push_back(v);
        				}
            }
        }
        defects.swap(newDefects);
    }
    this->center = new cv::Point(x, y);
}

Hand::~Hand() {
    delete this->center;
}

float Hand::distanceP2P(cv::Point a, cv::Point b){
	float d = sqrt(fabs( pow(a.x-b.x,2) + pow(a.y-b.y,2) )) ;
	return d;
}

float Hand::getAngle(cv::Point s, cv::Point f, cv::Point e){
  float l2 = distanceP2P(f,e);
	float l1 = distanceP2P(f,s);
	float dot=(s.x-f.x)*(e.x-f.x) + (s.y-f.y)*(e.y-f.y);
	float angle = acos(dot/(l1*l2));
	angle=angle*180/3.14159;
	return angle;
}

cv::Point* Hand::getCenter() {
    return this->center;
}

std::vector<cv::Point> Hand::getContour() {
    return this->contour;
}

std::vector<cv::Point> Hand::getHull(){
    return this->hull;
}

std::vector<cv::Vec4i> Hand::getDefects(){
    return this->defects;
}

void Hand::draw( Image * image ){
    std::vector<std::vector<cv::Point>> hulls = { this->hull };
    cv::drawContours(*image->getSrc(), hulls, 0, cv::Scalar(0, 255, 255));

    for (int i = 0; i < defects.size(); ++i) {
        int faridx = this->defects[i][1]; cv::Point ptFar(this->contour[faridx]);
        cv::circle(*image->getSrc(), ptFar, 4, cv::Scalar(255, 255,0), 2);
    }
}
