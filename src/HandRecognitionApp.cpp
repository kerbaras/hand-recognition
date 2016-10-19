//
// Created by Matias Pierobon on 8/21/16.
//

#include <iostream>
#include "HandRecognitionApp.h"
#include "recognition/HandRecognition.h"
#include "recognition/Video.h"
#include "recognition/Image.h"
#include "gui/opencv/Window.h"
#include "socket/Client.h"
#include "model/Point.h"
#include "recognition/VelocityRecognition.h"
#include "recognition/AngularRecognition.h"
#include <sys/types.h>
#include <sys/socket.h>

HandRecognitionApp::HandRecognitionApp() {

    Client * client = new Client("192.168.43.196", 5000);

    Video *video = new Video(0);
    HandRecognition * handRecognition = new HandRecognition("izquierda");

    handRecognition->waitForHand(video);

    Window window = Window("original");
    Window arrowWindow = Window("arrow");

    AngularRecognition * velocityRecognition = new AngularRecognition();
    int m0 = 0; int m1=0; std::string file; cv::Mat arrow;
    while(true){
        Image * image = video->getFrame();
        Hand * hand = handRecognition->getHand(image);
        hand->draw(image);

        int w = image->getSrc()->cols, h = image->getSrc()->rows;
        Point * center = new Point(w/2, h/2);
        velocityRecognition->fromHand(hand, center);

        int motor0 = -velocityRecognition->getMotor1();
        int motor1=-velocityRecognition->getMotor2();
        std::string descr = velocityRecognition->getDescriptor();
        if(descr != file) {
            file = descr;
            std::string str = "./arrows/" + file + ".png";
            arrow = cv::imread("./arrows/" + file + ".png");
            std::cout << str <<std::endl;
        }

        std::string msg;
        msg = "{\"task\":\"setSpeed\",\"m0\":" +
              std::to_string(motor0) + ",\"m1\":" +
              std::to_string(motor1) + "}";
        client->send(msg);
        std::cout << "(" << motor0 << ", " << motor1 << ")" <<std::endl;
        this->buildGUI(image, hand);

        window.show(image);
        delete image;

        if(arrow.rows > 0)
            cv::imshow("arrow", arrow);

        char c = cv::waitKey(1);

        if(c == char('q')){
          break;
        }else if( c == char('g')){
          handRecognition->waitForHand(video);
        }else if( c == char('c')){
            delete client;
            client = new Client("192.168.43.196", 5000);
        }else if (c == char('t')) {
          cv::Rect rect = cv::boundingRect(hand->getContour());
          //cv::Mat mask(rect.size(), cv::CV_U8C1);

        }
    }
    cv::destroyAllWindows();
    delete velocityRecognition;
    delete handRecognition;
    delete video;
    delete client;
}

void HandRecognitionApp::buildGUI( Image * image, Hand * hand){
        int w = image->getSrc()->cols, h = image->getSrc()->rows;
        Point * center = new Point(w/2, h/2);
        cv::circle(*image->getSrc(), cv::Point(center->getX(), center->getY()), w/10, cv::Scalar(0,10,127),2);
        cv::circle(*image->getSrc(), cv::Point(center->getX(), center->getY()), (w/10)*2, cv::Scalar(76,01,255),2);
        cv::circle(*image->getSrc(), cv::Point(center->getX(), center->getY()), (w/10)*3, cv::Scalar(0,16,204),2);
        cv::line(*image->getSrc(), cv::Point(center->getX(), center->getY()), *hand->getCenter(), cv::Scalar(0,220,115),1);
        //cv::line(*image->getSrc(), cv::Point(0, h/2), cv::Point(w,h/2), cv::Scalar(0,220,115),2);
}
