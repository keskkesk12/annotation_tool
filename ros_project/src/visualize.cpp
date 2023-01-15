#include <memory>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/msg/point.hpp"

#define WIDTH 54
#define HEIGHT 30

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

class Visualize : public rclcpp::Node
{
	public:
		Visualize() : Node("visualizer"){
			RCLCPP_INFO(this->get_logger(), "Initializing Visualize node");

			RCLCPP_INFO(this->get_logger(), "Starting camera subscription");


			// initialize subscriber
			camera_subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
					"/image_raw",
					1,
					std::bind(&Visualize::onImageMsg, this, std::placeholders::_1)
			);
            position_subscription_ = this->create_subscription<geometry_msgs::msg::Point>(
                "/hand_position",
                1,
                std::bind(&Visualize::onPositionMsg, this, std::placeholders::_1)
			);

		}

	private:
		rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr camera_subscription_;
		rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr position_subscription_;
        cv::Mat newest_image;
		void onImageMsg(const sensor_msgs::msg::Image::SharedPtr msg) {
			RCLCPP_INFO(this->get_logger(), "Received image!");
			// get image and format
			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
			newest_image = cv_ptr->image;

		}
        void onPositionMsg(const geometry_msgs::msg::Point p){
            if(newest_image.empty())
                return;
            float x = p.x/float(WIDTH)*newest_image.size().width;
            float y = p.y/float(HEIGHT)*newest_image.size().height;
            cv::Mat canvas;
            newest_image.copyTo(canvas);
            cv::resize(canvas, canvas, cv::Size(WIDTH, HEIGHT));
            cv::circle(canvas,cv::Point(int(p.x),int(p.y)),2,cv::Scalar(255,0,0),-1);
            std::cout << "x: " << p.x << " y: " << p.y << std::endl;
            cv::resize(canvas,canvas,cv::Size(540,300));
            cv::cvtColor(canvas, canvas, cv::COLOR_RGB2BGR);
            cv::imshow("Image",canvas);
            cv::waitKey(1);

        }
};


int main(int argc, char *argv[])
{
	setvbuf(stdout,NULL,_IONBF,BUFSIZ);

	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<Visualize>());

	rclcpp::shutdown();
	return 0;
}
