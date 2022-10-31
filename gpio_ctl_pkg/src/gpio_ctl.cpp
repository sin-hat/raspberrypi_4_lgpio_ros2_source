/*****************************************************************************************************/
/* software name: gpio_ctl.cpp                                                                       */
/* date: 2022/8/19                                                                                   */
/* name: Sin.Hat                                                                                     */
/* overview: for controlling raspberrypi 4 gpio, using LGPIO                                         */
/*****************************************************************************************************/
#include <rclcpp/rclcpp.hpp>
#include <lgpio.h>
#include "gpio_ctl.hpp"

/* constructor */
GpioCtl::GpioCtl(const rclcpp::NodeOptions & options) : Node(node_name, options)
{
  /* timer callback settings  */
  main_timer = this->create_wall_timer(main_timer_period, std::bind(&GpioCtl::main_timer_callback, this));
  /* subscriber, publisher settings */
  /* service, client settings */
  gpio_ctl_srv = this->create_service<custom_interfaces_pkg::srv::GpioPin>
                 ("gpio_ctl_command", std::bind(&GpioCtl::gpio_ctl_func, this, std::placeholders::_1, std::placeholders::_2));

  /* GPIO open */
  gpio_handle = lgGpiochipOpen(0);
  
  /* inform */
  RCLCPP_INFO(this->get_logger(), "GPIO open: handle:%d", gpio_handle);
}

/* destructor */
GpioCtl::~GpioCtl()
{
  /* GPIO close */
  lgGpiochipClose(gpio_handle);
  RCLCPP_INFO(this->get_logger(), "GPIO close: handle:%d", gpio_handle);
}

/* main_timer callback */
void GpioCtl::main_timer_callback()
{
  /* no action */
}

/* gpio_ctl service call */
void GpioCtl::gpio_ctl_func(const std::shared_ptr<custom_interfaces_pkg::srv::GpioPin::Request> request,
                            const std::shared_ptr<custom_interfaces_pkg::srv::GpioPin::Response> response)
{
  /* variable definition */
  int output_pin_number;
  bool output_pin_data;
  
  /* variable initialization */
  output_pin_number = request->pin_number;
  output_pin_data = 0;

  /* read/write checking */
  if(gpio_handle < 0)
  {
    /* error */
    RCLCPP_ERROR(this->get_logger(), "GPIO error: handle:%d", gpio_handle);
  }
  else if(request->pin_ctl_flag == 0)   /* if read */
  {
    /* read */
    output_pin_number = request->pin_number;
    lgGpioClaimInput(gpio_handle, lFags, output_pin_number);
    output_pin_data = lgGpioRead(gpio_handle, output_pin_number);
    
    /* inform */
    RCLCPP_INFO(this->get_logger(), "GPIO read: handle:%d number:%d data:%d", gpio_handle, output_pin_number, output_pin_data);
  }
  else if(request->pin_ctl_flag == 1)  /* if write */
  {
    /* write */
    lgGpioClaimOutput(gpio_handle, lFags, request->pin_number, request->pin_data);
    lgGpioWrite(gpio_handle, request->pin_number, request->pin_data);
    
    /*output*/
    output_pin_number = request->pin_number;
    output_pin_data = request->pin_data;
    
    /* inform */
    RCLCPP_INFO(this->get_logger(), "GPIO write: handle:%d number:%d data:%d", gpio_handle, output_pin_number, output_pin_data);
  }
  else
  {
    /* no action */
  }
  
  /* response */
  response->handle = gpio_handle;
  response->pin_number = output_pin_number;
  response->pin_data = output_pin_data;
}



