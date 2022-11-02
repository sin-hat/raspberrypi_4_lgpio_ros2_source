# ros2 test launch file
# 2022/08/23
# S.Hattori
import os
from launch import LaunchDescription
import launch.substitutions
from launch_ros.actions import Node

def generate_launch_description():
    # directory for parameter file
    parameter_file_path = launch.substitutions.LaunchConfiguration(
        'params', default=[launch.substitutions.ThisLaunchFileDir(), '/parameter_file_lgpio_test.yaml'])

    # Node list
    return LaunchDescription([
        Node(
            package = 'gpio_ctl_pkg',
            executable = 'gpio_ctl_node',
            name = 'gpio_ctl',
            output = 'screen',
            parameters = [parameter_file_path]
        )
    ])

