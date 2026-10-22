#ifndef THRUSTER_MANAGER_HPP
#define THRUSTER_MANAGER_HPP

#include "rclcpp/rclcpp.hpp"
#include <chrono>

#include "custom_interfaces/msg/pwm.hpp"
#include "custom_interfaces/msg/thruster_percents.hpp"
#include "std_msgs/msg/empty.hpp"

using namespace std::chrono_literals;

class ThrusterManager : public rclcpp::Node {
public:
    ThrusterManager();

private:
    void thruster_manager_callback(const custom_interfaces::msg::ThrusterPercents & msg) const;
    rclcpp::Subscription<custom_interfaces::msg::ThrusterPercents>::SharedPtr subscription;
    rclcpp::Publisher<custom_interfaces::msg::PWM>::SharedPtr pwm_publisher;

    constexpr static int kMidpointPwm = 1500;
    constexpr static int kPwmRange = 400;
    custom_interfaces::msg::PWM convert_percents_to_pwm(const custom_interfaces::msg::ThrusterPercents & msg) const;
    void set_pwm_limit(int limit);
    int pwmLimit = 200;

    void heartbeat_check_callback(const std_msgs::msg::Empty & msg);
    void heartbeat_publish_callback();
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr heartbeat_subscription;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr heartbeat_publisher;
    rclcpp::TimerBase::SharedPtr heartbeat_timer;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;
    constexpr static std::chrono::milliseconds kHeartbeatTimeout = 1000ms;
};

#endif // THRUSTER_MANAGER_HPP