// stdlib
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

// Opencv
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>

int main(){
  
  cv::Mat markerImage;
  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

  for(int i = 0; i < 10; i++){
    cv::aruco::drawMarker(dictionary, i, 200, markerImage, 1);
    cv::imwrite("markers/DICT_4x4_50_" + std::to_string(i) + ".png", markerImage);
  }
  return 0;
}