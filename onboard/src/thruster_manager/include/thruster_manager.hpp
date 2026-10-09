#ifndef THRUSTER_MANAGER_HPP
#define THRUSTER_MANAGER_HPP

#include "rclcpp/rclcpp.hpp"

#include "custom_interfaces/msg/pwm.hpp"
#include "custom_interfaces/msg/thruster_values.hpp"

class ThrusterManager : public rclcpp::Node {
public:
    ThrusterManager();

private:
    void thruster_manager_callback(const custom_interfaces::msg::ThrusterValues & msg) const;
    rclcpp::Subscription<custom_interfaces::msg::ThrusterValues>::SharedPtr subscription;

    custom_interfaces::msg::ThrusterValues thruster_values;
    int pwmLimit = 200;

    void timer_callback();
    rclcpp::Publisher<custom_interfaces::msg::PWM>::SharedPtr timer_manager;
    rclcpp::TimerBase::SharedPtr timer;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;
};

#endif // THRUSTER_MANAGER_HPP