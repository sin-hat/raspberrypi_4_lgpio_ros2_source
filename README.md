# raspberrypi_4_lgpio_ros2_source
This softwares are for RaspberryPI 4, Ubuntu22.04, LGPIO, and ros2(humble).

## Setup RaspberryPI 4
Please install Ubuntu 22.04.  
Ubuntu22.04: [https://ubuntu.com/download/raspberry-pi](https://ubuntu.com/download/raspberry-pi)
or
Ubuntu MATE22.04: [https://ubuntu-mate.org/raspberry-pi/](https://ubuntu-mate.org/raspberry-pi/)

I recommend ubuntu MATE.

## Install ROS2
Please install ROS2 hubmle.  
ROS2: [https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html)

## Install LGPIO
Please install LGPIO.  
LGPIO: [http://abyz.me.uk/lg/download.html](http://abyz.me.uk/lg/download.html)

## Download this src and colcon build
Create ros2 workspace folder and src folder.
Download this code and `colcon build`.

## Launch
`cd launch` and `ros2 launch ros2_lgpio_test.launch.py`.

## Read and Write
This software can control gpio using ROS2 service command.

### Read gpio data
This software only can do `lgGpioRead`command.  
If you want to read the 23 pin data, you do the comannd, as follows.  
`ros2 service call /gpio_ctl_command custom_interfaces_pkg/srv/GpioPin "{pin_ctl_flag: 0, pin_number: 23, pin_data: 0}"`  

pin_ctl_flag(bool): [0:read_mode, 1:write_mode]  
pin_bumber(int32): [the number of pin]  
pin_data(bool): [0 (If you choose write_mode, you must write the data in this section.)]  

### Write gpio data
This software only can do `lgGpioWrite`command.  
If you want to write 1 on the 23 pin, you do the comannd, as follows.   
`ros2 service call /gpio_ctl_command custom_interfaces_pkg/srv/GpioPin "{pin_ctl_flag: 1, pin_number: 23, pin_data: 1}"`  

pin_ctl_flag(bool): [0:read_mode, 1:write_mode]  
pin_bumber(int32): [the number of pin]  
pin_data(bool): [write the data you want to write in this section.]  
