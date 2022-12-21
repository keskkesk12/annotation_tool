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

  cv::Mat image = cv::imread("markers/test_image.jpg");
  cv::resize(image, image, cv::Size(720, 1280));

  std::vector<int> markerIds;
  std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
  cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
  cv::aruco::detectMarkers(image, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

  cv::Mat outputImage = image.clone();
  
  // Print
  for(int i = 0; i < markerIds.size(); i++){
    std::cout << "id: " << markerIds[i] << std::endl;
  }

  // Draw
  for(int i = 0; i < markerCorners.size(); i++){
    cv::Point2f center(0, 0);
    for(int j = 0; j < markerCorners[i].size(); j++){
      cv::Point2f p = markerCorners[i][j];
      cv::circle(outputImage, p, 2, cv::Scalar(125, 19, 244), -1);
      center += p;
    }
    center /= float(markerCorners[i].size());

    cv::circle(outputImage, center, 4, cv::Scalar(200, 0, 200), -1);
  }

  cv::imshow("Image", outputImage);
  cv::waitKey(-1);

  return 0;
}