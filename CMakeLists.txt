cmake_minimum_required(VERSION 3.21)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
project(simple-pubsub-broker)

# Find packages
find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(test)