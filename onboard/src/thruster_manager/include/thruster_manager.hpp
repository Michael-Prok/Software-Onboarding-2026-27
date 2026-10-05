#ifndef THRUSTER_MANAGER_HPP
#define THRUSTER_MANAGER_HPP

#include "rclcpp/rclcpp.hpp"

class ThrusterManager : public rclcpp::Node {
public:
    ThrusterManager();

private:
    void thruster_manager_callback(const std_msgs::msg::String & msg) const;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;

    void timer_callback();
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    rclcpp::TimerBase::SharedPtr timer;
    size_t count;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;
};

#endif // THRUSTER_MANAGER_HPP
