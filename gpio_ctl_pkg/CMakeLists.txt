cmake_minimum_required(VERSION 3.8)
project(gpio_ctl_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(custom_interfaces_pkg REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# build the node
add_library(gpio_ctl SHARED
  src/gpio_ctl.cpp
)
ament_target_dependencies(gpio_ctl
  rclcpp
  custom_interfaces_pkg
)
target_include_directories(gpio_ctl
  PUBLIC include/${PROJECT_NAME}
)

add_executable(gpio_ctl_node
  src/gpio_ctl_node.cpp
)
target_include_directories(gpio_ctl_node
  PUBLIC include/${PROJECT_NAME}
)

link_directories(/usr/local/lib)
target_link_libraries(gpio_ctl_node gpio_ctl lgpio)

install(TARGETS
  gpio_ctl
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
