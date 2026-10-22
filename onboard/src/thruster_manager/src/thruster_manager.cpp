#include <chrono>
#include <list>

#include "thruster_manager.hpp"

using namespace std::chrono_literals;

ThrusterManager::ThrusterManager() :
    Node("thruster_manager") {
    subscription = this->create_subscription<custom_interfaces::msg::ThrusterPercents>(
    "thruster_percents", 10, std::bind(&ThrusterManager::thruster_manager_callback, this, std::placeholders::_1));

    heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>(
    "gamepad_interpreter_heartbeat", 10, std::bind(&ThrusterManager::heartbeat_check_callback, this, std::placeholders::_1));

    pwm_publisher = this->create_publisher<custom_interfaces::msg::PWM>("pwm", 10);
    heartbeat_publisher = this->create_publisher<std_msgs::msg::Empty>("thruster_manager_heartbeat", 10);
    /* Creates a timer that triggers every half a second, calling the timer_callback() function
     * every half a second
    */
    heartbeat_timer = this->create_wall_timer(
    500ms, std::bind(&ThrusterManager::heartbeat_publish_callback, this));
    most_recent_heartbeat = std::chrono::steady_clock::now();
}

custom_interfaces::msg::PWM ThrusterManager::convert_percents_to_pwm(const custom_interfaces::msg::ThrusterPercents & msg) const {
    auto pwm = custom_interfaces::msg::PWM();
    if (most_recent_heartbeat + kHeartbeatTimeout > std::chrono::steady_clock::now()) {
    pwm.thruster_pwm_0 = msg.thruster_percent_0 * (kPwmRange - pwmLimit) + kMidpointPwm;
    pwm.thruster_pwm_1 = msg.thruster_percent_1 * (kPwmRange - pwmLimit) + kMidpointPwm;
    pwm.thruster_pwm_2 = msg.thruster_percent_2 * (kPwmRange - pwmLimit) + kMidpointPwm;
    pwm.thruster_pwm_3 = msg.thruster_percent_3 * (kPwmRange - pwmLimit) + kMidpointPwm;
    pwm.thruster_pwm_4 = msg.thruster_percent_4 * (kPwmRange - pwmLimit) + kMidpointPwm;
    pwm.thruster_pwm_5 = msg.thruster_percent_5 * (kPwmRange - pwmLimit) + kMidpointPwm;
    pwm.thruster_pwm_6 = msg.thruster_percent_6 * (kPwmRange - pwmLimit) + kMidpointPwm;
    pwm.thruster_pwm_7 = msg.thruster_percent_7 * (kPwmRange - pwmLimit) + kMidpointPwm;
    }
    return pwm;
}

void ThrusterManager::set_pwm_limit(int limit) {
    if (limit < 0) {
        limit = 0;
    } else if (limit > kPwmRange) {
        limit = kPwmRange;
    }
    ThrusterManager::pwmLimit = limit;
}

void ThrusterManager::thruster_manager_callback(const custom_interfaces::msg::ThrusterPercents & msg) const {
    auto pwm = ThrusterManager::convert_percents_to_pwm(msg);

    pwm_publisher->publish(pwm);
    // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", std::to_string(msg.front()).c_str());
}

void ThrusterManager::heartbeat_check_callback(const std_msgs::msg::Empty & msg) {
    (void)msg; // keep compiler happy about unused variable
    most_recent_heartbeat = std::chrono::steady_clock::now();
}

void ThrusterManager::heartbeat_publish_callback() {
    if (most_recent_heartbeat + kHeartbeatTimeout < std::chrono::steady_clock::now()) {
        auto pwm = custom_interfaces::msg::PWM();
        pwm.thruster_pwm_0 = kMidpointPwm;
        pwm.thruster_pwm_1 = kMidpointPwm;
        pwm.thruster_pwm_2 = kMidpointPwm;
        pwm.thruster_pwm_3 = kMidpointPwm;
        pwm.thruster_pwm_4 = kMidpointPwm;
        pwm.thruster_pwm_5 = kMidpointPwm;
        pwm.thruster_pwm_6 = kMidpointPwm;
        pwm.thruster_pwm_7 = kMidpointPwm;
        pwm_publisher->publish(pwm);
    }
    auto heartbeat_msg = std_msgs::msg::Empty();
    heartbeat_publisher->publish(heartbeat_msg);
}



#ifndef ENABLE_TESTING

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ThrusterManager>());
    rclcpp::shutdown();
    return 0;
}

#endif // ENABLE_TESTING
