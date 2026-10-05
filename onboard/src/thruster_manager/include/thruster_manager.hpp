#ifndef THRUSTER_MANAGER_HPP
#define THRUSTER_MANAGER_HPP

#include "rclcpp/rclcpp.hpp"

class ThrusterManager : public rclcpp::Node {
public:
    ThrusterManager();

private:
    void thruster_manager_callback(const std::list<int> & msg) const;
    rclcpp::Subscription<std::list<int>>::SharedPtr subscription;

    std::list<int> thruster_pwm;
    int pwmLimit = 200;

    void timer_callback();
    rclcpp::Publisher<std::list<int>>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;
};

#endif // THRUSTER_MANAGER_HPP
