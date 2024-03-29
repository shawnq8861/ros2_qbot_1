cmake_minimum_required(VERSION 3.5)
project(qbot_nodes_cpp)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

#
# need the following to enable building custom services
#
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/CameraCommand.srv"
  "srv/HeadingSpeed.srv"
  "msg/EncoderCounts.msg"
 )

#
# needed to enable using custom srv files
#
ament_export_dependencies(rosidl_default_runtime)

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
target_include_directories(talker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
target_include_directories(listener PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

add_executable(uvc_camera src/uvc_camera.cpp)
ament_target_dependencies(uvc_camera 
	rclcpp 
	std_msgs
	sensor_msgs
	OpenCV)
target_include_directories(uvc_camera PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
add_executable(realtime_tests src/realtime_tests.cpp)
ament_target_dependencies(realtime_tests 
	rclcpp 
	std_msgs
	sensor_msgs)
target_include_directories(realtime_tests PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

add_executable(base_controller src/base_controller.cpp)
ament_target_dependencies(base_controller 
  rclcpp
  geometry_msgs)
target_include_directories(base_controller PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

add_executable(local_planner src/local_planner.cpp)
ament_target_dependencies(local_planner 
  rclcpp
  geometry_msgs
  nav_msgs)
target_include_directories(local_planner PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
add_executable(motor_encoder_tests src/motor_encoder_tests.cpp)
ament_target_dependencies(motor_encoder_tests 
	rclcpp 
	std_msgs
	sensor_msgs)
target_include_directories(motor_encoder_tests PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
add_executable(motor_stop src/motor_stop.cpp)
ament_target_dependencies(motor_stop 
	rclcpp 
	std_msgs
	sensor_msgs)
target_include_directories(motor_stop PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

add_executable(motor_start src/motor_start.cpp)
ament_target_dependencies(motor_start 
	rclcpp 
	std_msgs
	sensor_msgs)
target_include_directories(motor_start PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
add_executable(encoder_test src/encoder_test.cpp)
ament_target_dependencies(encoder_test 
	rclcpp 
	std_msgs
	sensor_msgs)
target_include_directories(encoder_test PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

add_executable(motor_duty_cycle_test src/motor_duty_cycle_test.cpp)
ament_target_dependencies(motor_duty_cycle_test 
	rclcpp 
	std_msgs
	sensor_msgs)
target_include_directories(motor_duty_cycle_test PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

add_executable(odometry src/odometry.cpp)
  ament_target_dependencies(odometry 
    rclcpp
    geometry_msgs
    nav_msgs
    tf2_geometry_msgs)
target_include_directories(odometry PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

#
# need the following to enable using the custon srv
#
rosidl_target_interfaces(uvc_camera
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(local_planner
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(base_controller
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(odometry
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS 
  talker
  listener
  uvc_camera
  realtime_tests
  base_controller
  local_planner
  motor_encoder_tests
  motor_stop
  motor_start
  encoder_test
  motor_duty_cycle_test
  odometry
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY src launch rviz urdf meshes
  DESTINATION share/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
