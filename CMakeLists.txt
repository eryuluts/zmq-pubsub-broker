cmake_minimum_required(VERSION 3.21)

include(cmake/clang-cxx-dev-tools.cmake)

project(simple-pubsub-broker
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(models)