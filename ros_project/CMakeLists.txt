cmake_minimum_required(VERSION 3.8)
project(ros_project)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(dynamixel_sdk REQUIRED PATH ./dynamixel_sdk)
find_package(dynamixel_sdk_custom_interfaces REQUIRED)

include_directories(driver/include)


rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SetPosition.msg"
)

add_executable(helloworld src/helloworld.cpp)

add_executable(hand_detector src/hand_detector.cpp driver/src/bram_uio.cpp driver/src/xnn_inference.c driver/src/xnn_inference_linux.c driver/src/xnn_inference_sinit.c)
ament_target_dependencies(hand_detector rclcpp std_msgs OpenCV sensor_msgs cv_bridge geometry_msgs)

add_executable(arm_controller src/arm_controller.cpp)
ament_target_dependencies(arm_controller rclcpp std_msgs geometry_msgs dynamixel_sdk_custom_interfaces dynamixel_sdk)

add_executable(read_write_node src/read_write_node.cpp)
ament_target_dependencies(read_write_node rclcpp dynamixel_sdk_custom_interfaces dynamixel_sdk)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


install(TARGETS helloworld
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS hand_detector
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS arm_controller
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
