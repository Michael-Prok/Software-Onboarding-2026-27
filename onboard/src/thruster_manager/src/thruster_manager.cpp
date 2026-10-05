#include <chrono>
#include <list>

#include "thruster_manager.hpp"

using namespace std::chrono_literals;

ThrusterManager::ThrusterManager() :
    Node("thruster_manager") {

    subscription = this->create_subscription<std::list<int>>(
    "thruster_percents", 10, std::bind(&ThrusterManager::thruster_manager_callback, this, std::placeholders::_1));

    publisher = this->create_publisher<std::list<int>>("topic", 10);
    /* Creates a timer that triggers every half a second, calling the timer_callback() function
     * every half a second
    */
    timer = this->create_wall_timer(
    500ms, std::bind(&ThrusterManager::timer_callback, this));
}

void ThrusterManager::thruster_manager_callback(const std::list<int> & msg) const {
    ThrusterManager::thruster_pwm = msg;
    for (const auto& num : thruster_pwm) {
        num * (400 - pwmLimit) + 1500;
    }
    // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", std::to_string(msg.front()).c_str());
}

void ThrusterManager::timer_callback() {
    
    RCLCPP_INFO(this->get_logger(), "Publishing PWM List: '%s'", std::to_string(thruster_pwm.front()).c_str());
    publisher->publish(thruster_pwm);
}



#ifndef ENABLE_TESTING

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ThrusterManager>());
    rclcpp::shutdown();
    return 0;
}

#endif // ENABLE_TESTING
