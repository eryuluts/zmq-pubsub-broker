add_executable(broker broker.cpp)
target_link_libraries(broker
    PRIVATE
        fmt::fmt
)

add_executable(publisher publisher.cpp)
target_link_libraries(publisher
    PRIVATE
        fmt::fmt
)

add_executable(subscriber subscriber.cpp)
target_link_libraries(subscriber
    PRIVATE
        fmt::fmt
)

