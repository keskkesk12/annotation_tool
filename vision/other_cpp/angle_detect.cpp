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

#include <eigen3/Eigen/Dense>



using Eigen::Vector2f;

int main() {
  // Opencv window
  std::string name = "Image";
  cv::namedWindow(name);

  // Output streams for writing labels
  std::ofstream labels("../training_labels/labels.csv");

  bool running = true;
  cv::Size image_size(1920, 1080);

  int index = 0;

  // Videos in folder
  for (const auto & entry : std::filesystem::directory_iterator("../raw_data")){
    cv::VideoCapture capture(entry.path());
    // cv::VideoCapture capture(0);
    cv::Mat frame;

    // Process each frame
    while (true){
      capture >> frame;
      if (frame.empty()){
        break;
      }

      // Process frame
      cv::resize(frame, frame, image_size);
      std::vector<int> markerIds;
      std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
      cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
      cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
      cv::aruco::detectMarkers(frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);


      // Draw points on image if all points are detected
      if(markerIds.size() == 3){

        std::vector<cv::Point2f> centers;
        for(int i = 0; i < markerCorners.size(); i++){
          auto index = find(markerIds.begin(), markerIds.end(), i);
          if(index == markerIds.end()){
            continue;
          }

          cv::Point2f center;

          for(int j = 0; j < markerCorners[index - markerIds.begin()].size(); j++){
            center += markerCorners[index - markerIds.begin()][j];
          }
          center /= 4.0;
          centers.push_back(center);
        }

        for(int i = 0; i < centers.size(); i++){
          // Draw circles
          cv::circle(frame, centers[i], 8, cv::Scalar(0, 255, 255), 2);
          // Draw lines
          if(i > 0){
            cv::line(frame, centers[i-1], centers[i], cv::Scalar(255, 0, 0), 3);
          }
        }

        // Calculate angles
        float shoulder_angle = atan2(centers[1].y - centers[0].y , centers[1].x - centers[0].x);
        float elbow_angle = atan2(centers[2].y - centers[1].y , centers[2].x - centers[1].x);
        std::cout << shoulder_angle << ", " << elbow_angle << std::endl;

        std::stringstream ss;
        ss << std::setw(6) << std::setfill('0') << index++;
        std::string s = ss.str();


        cv::Mat frame_out;
        cv::resize(frame, frame_out, cv::Size(16*3, 9*3));
        cv::cvtColor(frame_out, frame_out, cv::COLOR_BGR2GRAY);

        cv::imwrite("../training_data/" + s + ".png", frame_out);

        labels << shoulder_angle << ", " << elbow_angle << "\n";
      }

      // Visualize output
      // cv::imshow(name, frame);
      // char key = cv::waitKey(2);      
      // if(key == 'q'){
      //   running = false;
      //   break;
      // }
    }
  }

  labels.close();

  return 0;
}