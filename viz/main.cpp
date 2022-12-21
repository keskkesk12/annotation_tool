// stdlib
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

// Opencv
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

std::vector<std::vector<float>> readFile(std::string path){
  std::vector<std::vector<float>> angles;
  std::ifstream csv_file(path);
  std::string line;

  while(std::getline(csv_file, line)){
    std::stringstream ss(line);
    std::vector<float> angle_pair;
    while(ss.good()){
        std::string substr;
        std::getline( ss, substr, ',' );
        angle_pair.push_back(std::stof(substr));
    }
    angles.push_back(angle_pair);
  }
  csv_file.close();
  return angles;
}


int main()
{
  std::string name = "Image";
  cv::namedWindow(name);

  // std::string path = "output.csv";
  std::string path = "../training_labels/labels.csv";
  auto angles = readFile(path);
  
  // Image canvas
  cv::Mat canvas = cv::Mat::zeros(cv::Size(400, 400), CV_8UC3);
  cv::Point p0(350, 150);
  int l1 = 120;
  int l2 = 120;

  // Draw angles
  for(int i = 0; i < angles.size(); i++){
    canvas = cv::Mat::zeros(canvas.size(), canvas.type());

    float a1 = angles[i][0];
    float a2 = angles[i][1];
    cv::Point p1 = p0 + cv::Point(cos(a1)*l1, sin(a1)*l1);
    cv::Point p2 = p1 + cv::Point(cos(a2)*l2, sin(a2)*l2);
    
    cv::line(canvas, p0, p1, cv::Scalar(0, 255, 0), 1);
    cv::line(canvas, p1, p2, cv::Scalar(0, 0, 255), 1);
    // cv::line(canvas, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255, 255, 255), 10);

    cv::imshow(name, canvas);
    cv::waitKey(20);

    // std::cout << p0 << p1 << p2 << std::endl;
    // std::cout << angles[i][0] << ", " << angles[i][1] << std::endl;
  }
  cv::destroyAllWindows();

  return 0;
}