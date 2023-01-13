#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"

using std::placeholders::_1;

float map(float val, float old_min, float old_max, float new_min, float new_max){
  return new_min + ((new_max - new_min) / (old_max - old_min)) * (val - old_min);
}

float constrain(float val, float min, float max){
  if(val < min) val = min;
  if(val > max) val = max;
  return val;
}

float constrainedMap(float val, float old_min, float old_max, float new_min, float new_max){
  return map(constrain(val, old_min, old_max), old_min, old_max, new_min, new_max);
}

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
      float min = 9.5;
      float max = 13.5;

      float frame_w = 54.;
      float frame_h = 30.;

      float l1 = 7.;
      float l2 = 6.5;

      float w = 4.;
      float h = 2.22;

      float x = msg.x * w / frame_w + min;
      float y = h / 2. - msg.y * h / frame_h;

      float theta2 = acos(constrain((std::pow(x, 2) + std::pow(y, 2) - std::pow(l1, 2) - std::pow(l2, 2)) / (2 * l1 * l2), -1 ,1));
      float theta1 = atan2(y, x) - atan2((l2*sin(theta2)), (l1 + l2 * cos(theta2)));
      std::cout << "theta1=" << theta1 << " theta2=" << theta2 << std::endl;
      int32_t motor_val1 = constrainedMap(theta1 * 180./3.14159, -100, 100, 172, 854);
      int32_t motor_val2 = constrainedMap(theta2 * 180./3.14159, -100, 100, 172, 854);
      std::cout << "motor_val1=" << motor_val1 << " motor_val2=" << motor_val2 << std::endl;


      dynamixel_sdk_custom_interfaces::msg::SetPosition m1;

      m1.id = 0;
      m1.position = motor_val1;
      publisher_->publish(m1);
      dynamixel_sdk_custom_interfaces::msg::SetPosition m2;

      m2.id = 1;
      m2.position = motor_val2;
      publisher_->publish(m2);

    }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmController>());
  rclcpp::shutdown();
  return 0;
}