#include <stdio.h>
#include <memory>
#include <string>
#include <sched.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "roboclaw.hpp"

static constexpr int node_priority = 97;

class MotorEncoderTest : public rclcpp::Node
{
public:
    MotorEncoderTest()
    : Node("motor_encoder_tests"), count_(0)
    {
    }

private:
    size_t count_;

};

void enumerate_ports()
{
	std::vector<serial::PortInfo> devices_found = serial::list_ports();

	std::vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while( iter != devices_found.end() )
	{
		serial::PortInfo device = *iter++;

        RCLCPP_INFO_STREAM(rclcpp::get_logger("rclcpp"), "port: " << device.port.c_str()
                            << " description: " << device.description.c_str()
                            << " hardware_id: " << device.hardware_id.c_str());
	}
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    //
    // create the node
    //
    auto motor_encoder_test_node = std::make_shared<MotorEncoderTest>();
    //
    // use rt extensions
    //
    int rc = -1;
	struct sched_param my_params;
	// Passing zero specifies caller’s (our) policy
	my_params.sched_priority = node_priority;
    //
	// Passing zero specifies callers (our) pid
    // Set policy to SCHED_RR, no preemption with time slicing
    //
	rc = sched_setscheduler(0, SCHED_RR, &my_params);
    if ( rc == -1 ) {
        std::cout << "could not change scheduler policy" << std::endl;
    }
    else {
        std::cout << "changed scheduler policy" << std::endl;
    }

    //
    // lock memory to prevent paging
    //
    //mlockall(MCL_CURRENT | MCL_FUTURE);

    // Do stuff here......
    RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), "motor and encoder tests... ");
    //
    // try to open a port
    //
    // port, baudrate, timeout in milliseconds
    //
    std::string port("/dev/ttymxc2");
    unsigned long baud = 38400;
    serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000));
    //
    // lock memory to prevent paging after instantiations are complete
    //
    mlockall(MCL_CURRENT | MCL_FUTURE);
    //
    // check if the serial port is open
    //
    RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), "Is the serial port open?");
    if(my_serial.isOpen()) {
        RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), " Yes. open, testing...\n\n");

        // Test the timeout, there should be 1 second between prints
        RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), "Timeout == 1000ms, asking for 1 more byte than written.");
        int count = 0;
        std::string test_string("Testing.");
        while (count < 10) {
            size_t bytes_wrote = my_serial.write(test_string);

            std::string result = my_serial.read(test_string.length()+1);

            RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(),"Iteration: " << count);
            RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), ", Bytes written: " << bytes_wrote);
            RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), ", Bytes read: " << result.length());
            RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), ", String read: " << result);

            count += 1;
        }

        my_serial.close();
    }
    else {
        RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), " No.");
    }
    //Roboclaw robo = Roboclaw(port, baud);
    //uint8_t address = 0x80;
    //uint8_t status = 0;
    //bool valid = false;
    //uint32_t motor1_position = -1;
    //motor1_position = robo.ReadEncM1(address, &status, &valid);
    //RCLCPP_INFO_STREAM(motor_encoder_test_node->get_logger(), "motor1 position:  " << motor1_position);

    //
    // unlock memory before teardown
    //
    munlockall();
    

    rclcpp::shutdown();
    return 0;
}