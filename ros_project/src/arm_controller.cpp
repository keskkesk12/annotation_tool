#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


using std::placeholders::_1;

class ArmController : public rclcpp::Node {
public:
  ArmController() : Node("arm_controller") {
    //publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces/msg/SetPosition>("set_position", 1);
    subscription_ = this->create_subscription<std_msgs::msg::String>("hand_position", 1, std::bind(&ArmController::topic_callback, this, _1));
  }

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;

  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
      //RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
      std::cout << "Message received " << msg->data.c_str() << std::endl;
    }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmController>());
  rclcpp::shutdown();
  return 0;
}