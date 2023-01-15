#include <memory>
#include <string>
#include <iostream>

#include "bram_uio.hpp"
#include "xnn_inference.h"
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/msg/point.hpp"

#define width 54
#define height 30

std::vector<float> img2vec(cv::Mat img)
{

    std::vector<float> pixelvals;

    for(int i = 0; i < img.rows; i++)
    {
        for(int j = 0; j < img.cols; j++)
        {
            float pixel = img.at<uint8_t>(i, j)/255.0;
            pixelvals.push_back(pixel);
        }
    }

    return pixelvals; 
}

class HandDetector : public rclcpp::Node
{
	public:
		HandDetector() : Node("image_subscriber"), bram_input(0,0x2000), bram_output(1,0x1000) {
			RCLCPP_INFO(this->get_logger(), "Initializing HandDetector node");


			// initialize nn_inference
			InstancePtr = new XNn_inference;
  			InstancePtr->Axi_cpu_BaseAddress = 0xa0030000;
  			InstancePtr->IsReady = false;
  			const char* InstanceName = "nn_inference";
    		int status = XNn_inference_Initialize(InstancePtr ,InstanceName);
  			assert(status == XST_SUCCESS);

			RCLCPP_INFO(this->get_logger(), "Starting camera subscription");

			// initialize subscriber
			camera_subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
					"/image_raw",
					1,
					std::bind(&HandDetector::onImageMsg, this, std::placeholders::_1)
			);

			// initialize publisher
			position = this->create_publisher<geometry_msgs::msg::Point>("hand_position", 1);
		}

	private:
		rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr camera_subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr position;
    XNn_inference *InstancePtr;
    BRAM bram_input;
    BRAM bram_output;
		void onImageMsg(const sensor_msgs::msg::Image::SharedPtr msg) {
			RCLCPP_INFO(this->get_logger(), "Received image!");

			// get image and format
			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
			cv::Mat img = cv_ptr->image;
			cv::resize(img, img, cv::Size(width, height), cv::INTER_AREA);
			cv::cvtColor(img, img, CV_RGB2GRAY);

      // image as vector
      std::vector<float> img_vector = img2vec(img);

	 		// wait for network to be ready
	 		while(!XNn_inference_IsReady(InstancePtr));

	 		// banish to BRAM_input
     	for(int i = 0; i < img_vector.size(); i++)
       {
         bram_input[i] = *((u32*)&(img_vector[i]));
       }

       // start network and wait for it to finish
       XNn_inference_Start(InstancePtr);
       while(!XNn_inference_IsIdle(InstancePtr)) {};

      // create and publish position
			geometry_msgs::msg::Point p;
			p.x = *(float*)&(bram_output[0]);
			p.y = *(float*)&(bram_output[1]);
			//p.x = 10;
			//p.y = 11;
			p.z = 0.0;
			position->publish(p);
		}
};

int main(int argc, char *argv[])
{
	setvbuf(stdout,NULL,_IONBF,BUFSIZ);

	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<HandDetector>());

	rclcpp::shutdown();
	return 0;
}
