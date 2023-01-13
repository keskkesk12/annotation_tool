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
#include <random>

// Opencv
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>


cv::Mat translateImg(cv::Mat &img, int offsetx, int offsety, float ang, float zoom){
  cv::Size size = img.size();

  float x = size.width/2;
  float y = size.height/2;

  cv::Mat r = cv::getRotationMatrix2D(cv::Point2f(x, y), ang*180.0/M_PI, zoom);

  r.at<double>(0, 2) += offsetx;
  r.at<double>(1, 2) += offsety;

  cv::warpAffine(img,img,r,img.size());
  return img;
}


void augmentImage(cv::Mat& img){
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::normal_distribution<> x_distr(0, .125);
  std::normal_distribution<> y_distr(0, .125);
  std::normal_distribution<> rot_distr(0, M_PI/7);
  std::normal_distribution<> zoom_distr(1.125, .2);

  cv::Size size = img.size();
  translateImg(img, size.width*x_distr(gen), size.height*y_distr(gen), rot_distr(gen), zoom_distr(gen));

  // Brightness augmentation
  std::normal_distribution<> alpha_distr(1, .4);
  std::normal_distribution<> beta_distr(0, .4);
  img.convertTo(img, -1, alpha_distr(gen), beta_distr(gen));
}




int main() {
  // Opencv window
  std::string name = "Image";
  cv::namedWindow(name);

  // Output streams for writing labels
  std::ofstream labels("../training_labels/labels.csv");

  bool running = true;
  cv::Size image_size(1280, 720);
  cv::Size output_size(48*3, 27*3);
  cv::Mat heat_map(image_size, CV_8UC1, cv::Scalar(0));

  int index = 0;
  int aug_num = 10;

  // Videos in folder
  for (const auto & entry : std::filesystem::directory_iterator("../raw_data")){
    cv::VideoCapture capture(entry.path());
    // cv::VideoCapture capture(0);
    cv::Mat frame;

    // Process each frame
    while (running){
      capture >> frame;
      if (frame.empty()){
        break;
      }
      cv::Mat aug_frame;

      for(int k = 0; k < aug_num; k++){
        frame.copyTo(aug_frame);
        augmentImage(aug_frame);

        // Process frame
        cv::resize(aug_frame, aug_frame, image_size);
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
        cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
        cv::aruco::detectMarkers(aug_frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
                
        // Draw points on image if all points are detected
        if(markerIds.size() == 1){

          cv::Point2f center;
          for(int j = 0; j < markerCorners[0].size(); j++){
            center += markerCorners[0][j];
          }
          center /= 4.0;

          // Draw on heatmap
          heat_map.at<char>(center) = 255;

          std::vector<std::vector<cv::Point>> contours;
          std::vector<cv::Point> contour;
          for(int i = 0; i < markerCorners[0].size(); i++){
            cv::Point p = cv::Point(int(markerCorners[0][i].x), int(markerCorners[0][i].y));
            cv::Point int_center(center.x, center.y);
            cv::Point dif = int_center - p;

            contour.push_back(int_center - dif*1.9);
          }
          contours.push_back(contour);

          // Draw mask
          cv::Mat mask(image_size, CV_8UC1, cv::Scalar(0));
          cv::drawContours(mask, contours, 0, 255, -1);


          // Draw center
          cv::circle(aug_frame, center, 8, cv::Scalar(255, 0, 255), 2);

          std::stringstream ss;
          ss << std::setw(6) << std::setfill('0') << index++;
          std::string s = ss.str();

          cv::inpaint(aug_frame, mask, aug_frame, 20, cv::INPAINT_TELEA);

          // std::cout << center.x << ", " << center.y << std::endl;
          std::cout << index << std::endl;

          cv::Mat frame_out;
          cv::resize(aug_frame, frame_out, output_size);
          cv::cvtColor(frame_out, frame_out, cv::COLOR_BGR2GRAY);

          cv::imwrite("../training_data/" + s + ".bmp", frame_out);

          labels << center.x/float(image_size.width) << ", " << center.y/float(image_size.height) << "\n";

          // Visualize output
          // cv::imshow(name, aug_frame);
          // char key = cv::waitKey(-1);
          // if(key == 'q'){
          //   running = false;
          //   break;
          // }
        }
      }
    }
  }

  cv::imshow(name, heat_map);
  cv::waitKey(-1);

  labels.close();

  return 0;
}