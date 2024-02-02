set(TARGET_NAME broker)
add_executable(${TARGET_NAME} broker.cpp)
target_link_libraries(${TARGET_NAME}
    PRIVATE
        fmt::fmt
)