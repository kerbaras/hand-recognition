cmake_minimum_required(VERSION 3.5)
project(HandRecognition)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )

set(SOURCE_FILES src/main.cpp src/HandRecognitionApp.cpp src/HandRecognitionApp.h src/recognition/Video.cpp src/recognition/Video.h src/recognition/Image.cpp src/recognition/Image.h src/recognition/RoI.cpp src/recognition/RoI.h src/recognition/HandRecognition.cpp src/recognition/HandRecognition.h src/model/Hand.cpp src/model/Hand.h src/model/Point.cpp src/model/Point.h src/gui/opencv/Window.cpp src/gui/opencv/Window.h src/socket/Client.cpp src/socket/Client.h src/recognition/VelocityRecognition.cpp src/recognition/VelocityRecognition.h)
add_executable(HandRecognition ${SOURCE_FILES})
target_link_libraries( HandRecognition ${OpenCV_LIBS} )