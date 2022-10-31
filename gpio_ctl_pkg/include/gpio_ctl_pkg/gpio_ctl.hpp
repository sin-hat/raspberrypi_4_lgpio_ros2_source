/*****************************************************************************************************/
/* software name: gpio_ctl.hpp                                                                       */
/* date: 2022/8/19                                                                                   */
/* name: Sin.Hat                                                                                     */
/* overview:                                                                                         */
/*****************************************************************************************************/
/* include guard */
#ifndef GPIO_CTL_HPP
#define GPIO_CTL_HPP

/* include files */
#include <rclcpp/rclcpp.hpp>
#include <custom_interfaces_pkg/srv/gpio_pin.hpp>
#include <chrono>

/* namespace */
namespace
{
  /* node name */
  const std::string node_name = "gpio_ctl";
  /* buffer size */
  const int buffer_size = 10;
  /* timer callback period(ms) */
  const std::chrono::nanoseconds main_timer_period = std::chrono::milliseconds(500);
  /* lFags */
  const int lFags = 0;
}

/* class definition */
class GpioCtl : public rclcpp::Node
{
  public:
    GpioCtl(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());     /* constructor */
    ~GpioCtl();                                                              /* destructor */

  private:
    /* timer callback definition */
    rclcpp::TimerBase::SharedPtr main_timer;
    
    /* subscriber, publisher definition */
    
    /* service, client definition */
    rclcpp::Service<custom_interfaces_pkg::srv::GpioPin>::SharedPtr gpio_ctl_srv;
    
    /* function definition */
    void main_timer_callback();
    void gpio_ctl_func(const std::shared_ptr<custom_interfaces_pkg::srv::GpioPin::Request> request,
                       const std::shared_ptr<custom_interfaces_pkg::srv::GpioPin::Response> response);
                       
    /* variable definition */
    int gpio_handle;
};

#endif /* GPIO_CTL_HPP */


