add_executable(pubsubservice broker.cpp broker.hpp)
target_link_libraries(pubsubservice
    PRIVATE
        fmt::fmt
        pubsubservice_models
        cppzmq
)

add_library(pubsubservice_interface subscriber.cpp subscriber.hpp publisher.cpp publisher.hpp)
target_link_libraries(pubsubservice_interface
    PUBLIC
        pubsubservice_models
    PRIVATE
        fmt::fmt
        cppzmq
)
target_include_directories(pubsubservice_interface
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)