#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class HandDetector : public rclcpp::Node {
public:
  HandDetector() : Node("hand_detector"), count_(0) {
    publisher_ = this->create_publisher<std_msgs::msg::String>("hand_position", 10);
  }

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<HandDetector>());
  rclcpp::shutdown();
  return 0;
}