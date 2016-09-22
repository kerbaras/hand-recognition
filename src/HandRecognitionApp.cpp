//
// Created by Matias Pierobon on 8/21/16.
//

#include <iostream>
#include "HandRecognitionApp.h"
#include "recognition/HandRecognition.h"
#include "recognition/Video.h"
#include "recognition/Image.h"
#include "model/Hand.h"
#include "gui/opencv/Window.h"
#include "socket/Client.h"
#include "model/Point.h"
#include "recognition/VelocityRecognition.h"
#include "recognition/AngularRecognition.h"
#include <sys/types.h>
#include <sys/socket.h>



HandRecognitionApp::HandRecognitionApp() {

    Client * client = new Client("192.168.43.196", 5000);

    Video *video = new Video(1);
    HandRecognition * handRecognition = new HandRecognition("izquierda");

    handRecognition->waitForHand(video);

    Window window = Window("original");

    AngularRecognition * velocityRecognition = new AngularRecognition();
    int m0 = 0; int m1=0;
    while(true){
        Image * image = video->getFrame();
        Hand * hand = handRecognition->getHand(image);

        std::vector<std::vector<cv::Point>> hulls = { hand->getHull() };

        cv::drawContours(*image->getSrc(), hulls, 0, cv::Scalar(0, 255, 255));

        std::vector<cv::Vec4i> defects = hand->getDefects();
        for (int i = 0; i < defects.size(); ++i) {
            int faridx = defects[i][1]; cv::Point ptFar(hand->getContour()[faridx]);
            cv::circle(*image->getSrc(), ptFar, 4, cv::Scalar(255, 255,0), 2);
        }

        int w = image->getSrc()->cols, h = image->getSrc()->rows;
        Point * center = new Point(w/2, h/2);
        velocityRecognition->fromHand(hand, center);
        int motor0 = -velocityRecognition->getMotor2(); int motor1=-velocityRecognition->getMotor1();

            m0 = motor0;
            m1 = motor1;
            std::string msg;
            msg = "{\"task\":\"setSpeed\",\"m0\":" + std::to_string(m0) + ",\"m1\":" + std::to_string(m1) + "}";
            client->send(msg);

        cv::circle(*image->getSrc(), cv::Point(center->getX(), center->getY()), w/8, cv::Scalar(0,10,127),2);
        cv::circle(*image->getSrc(), cv::Point(center->getX(), center->getY()), (w/8)*2, cv::Scalar(76,01,255),2);
        cv::circle(*image->getSrc(), cv::Point(center->getX(), center->getY()), (w/8)*3, cv::Scalar(0,16,204),2);
        cv::line(*image->getSrc(), cv::Point(center->getX(), center->getY()), *hand->getCenter(), cv::Scalar(0,220,115),1);
        cv::line(*image->getSrc(), cv::Point(0, h/2), cv::Point(w,h/2), cv::Scalar(0,220,115),2);
        //cv::line(*image->getSrc(), cv::Point(0, 0), cv::Point(w,h), cv::Scalar(0,220,115),2);
        //cv::line(*image->getSrc(), cv::Point(w, 0), cv::Point(0, h), cv::Scalar(0,220,115),2);
        window.show(image);
        delete image;

        char c = cv::waitKey(1);

        if(c == char('q')){
          break;
        }else if( c == char('i')){
          window.destroy();
          handRecognition->waitForHand(video);
        }
    }

    delete velocityRecognition;
    delete handRecognition;
    delete video;
    delete client;

}
