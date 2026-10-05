#include <chrono>

#include "thruster_manager.hpp"

using namespace std::chrono_literals;

ThrusterManager::ThrusterManager() :
    Node("thruster_manager") {

    subscription = this->create_subscription<std_msgs::msg::String>(
    "thruster_percents", 10, std::bind(&ThrusterManager::thruster_manager_callback, this, std::placeholders::_1));

    /* Creates a publisher that publishes a String message to a topic with name "topic" */
    publisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
    /* Creates a timer that triggers every half a second, calling the timer_callback() function
     * every half a second
    */
    timer = this->create_wall_timer(
    500ms, std::bind(&ThrusterManager::timer_callback, this));
}

void ThrusterManager::thruster_manager_callback(const std_msgs::msg::String & msg) const {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
}

void ThrusterManager::timer_callback() {
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher->publish(message);
}



#ifndef ENABLE_TESTING

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ThrusterManager>());
    rclcpp::shutdown();
    return 0;
}

#endif // ENABLE_TESTING
