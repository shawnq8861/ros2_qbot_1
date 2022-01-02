//
// common robot hardware and software configuration parameters
//

#ifndef ROBOT_CONFIGURATION
#define ROBOT_CONFIGURATION

static constexpr int base_controller_priority = 97;
static constexpr int local_planner_priority = 96;
static constexpr int8_t max_retries = 5;
static constexpr double wheel_base = 18.0;
static constexpr double wheel_diameter = 6.0;
static constexpr double rpm_max = 192.0;
static constexpr double pi = 3.1415926;
//
// max_v_forward = (rpm_max / 60.0) * pi * wheel_diameter = 60.318 in/sec
//
static constexpr double max_v_forward = 60.0;
static constexpr double max_delta_v = 1.5;
//
// max_v_angular = max_v_forward / (wheel_base / 2.0) = 6.702
//
static constexpr double max_v_angular = pi / 4.0;
static constexpr double max_delta_omega = pi / 90.0;

#endif // ROBOT_CONFIGURATION