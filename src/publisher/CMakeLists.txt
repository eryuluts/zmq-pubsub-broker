set(TARGET_NAME publisher)
add_executable(${TARGET_NAME} publisher.cpp)
target_link_libraries(${TARGET_NAME}
    PRIVATE
        fmt::fmt
)