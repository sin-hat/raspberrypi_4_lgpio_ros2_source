/*****************************************************************************************************/
/* software name: gpio_ctl_node.cpp                                                                           */
/* date: 2022/8/19                                                                                   */
/* name: Sin.Hat                                                                                     */
/* overview:                                                                                         */
/*****************************************************************************************************/
/* include file */
#include "gpio_ctl.hpp"

/* main funtion */
int main(int argc, char * argv[])
{
  /* Force flush of the stdout buffer. */
  setvbuf(stdout, nullptr, _IONBF, BUFSIZ);

  /* Ros2 settings */
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GpioCtl>());
  rclcpp::shutdown();
  return 0;
}
