set(TARGET_NAME subscriber)
add_executable(${TARGET_NAME} subscriber.cpp)
target_link_libraries(${TARGET_NAME}
    PRIVATE
        fmt::fmt
)