#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
#define a1_len 5
#define a2_len 5

using std::placeholders::_1;

class ArmController : public rclcpp::Node {
public:
  ArmController() : Node("arm_controller") {
    publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 1);
    subscription_ = this->create_subscription<geometry_msgs::msg::Point>("hand_position", 1, std::bind(&ArmController::topic_callback, this, _1));
  }

private:
  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;

  void topic_callback(const geometry_msgs::msg::Point msg) const
    {
      //RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());

      float theta2 = acos((std::pow(msg.x, 2) + std::pow(msg.y, 2) - std::pow(a1_len, 2) - std::pow(a2_len, 2)) / (2*a1_len*a2_len));
      float theta1 = atan2(msg.y, msg.x) - atan2((a2_len*sin(theta2)), (a1_len + a2_len*cos(theta2)));

      std::cout << "theta1: " << theta1 << ", theta2: " << theta2 << std::endl;

      dynamixel_sdk_custom_interfaces::msg::SetPosition out;
      out.id = 0;
      out.position = 300;
      publisher_->publish(out);
    }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmController>());
  rclcpp::shutdown();
  return 0;
}