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
#include <sys/types.h>
#include <sys/socket.h>



HandRecognitionApp::HandRecognitionApp() {

    Client * client = new Client("192.168.43.196", 5000);

    Video *video = new Video(0);
    HandRecognition * handRecognition = new HandRecognition("izquierda");

    handRecognition->waitForHand(video);

    Window window = Window("original");

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

        int m0 = 0; int m1=0;

        int x = hand->getCenter()->x, y = hand->getCenter()->y;
        int w = image->getSrc()->cols, h = image->getSrc()->rows;
        int gap = (h/(2*3)) - 5, vgap = w/3;

        Point * center = new Point(w/2, h/2);


        if(y==0){

        }else if (y < h/2 - 5){
            if(y < gap){
                m0 = 3; m1=3;
            }else if(y < gap * 2){
                m0 = 2; m1=2;
            }else{
                m0 = 1; m1=1;
            }

            if(x==0){

            }else if(x<vgap){
                m1 = m1 - 1;
            }else if(x > vgap*2){
                m0 = m0 -1;
            }

            m0 = m0 * (-1);
            m1 = m1 * (-1);

            std::string msg;
            msg = "{\"task\":\"chspeed\",\"m0\":" + std::to_string(m0) + ",\"m1\":" + std::to_string(m1) + "}";
            client->send(msg);
        }

        std::string msg;
        msg = "{\"task\":\"chspeed\",\"m0\":" + std::to_string(m0) + ",\"m1\":" + std::to_string(m1) + "}";
        client->send(msg);

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

    delete handRecognition;
    delete video;
    delete client;

}
