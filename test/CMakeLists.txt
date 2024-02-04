include(GoogleTest)


# Generate Test Models
set(TARGET_NAME test_models)
add_library(${TARGET_NAME} OBJECT test_models.proto)
target_link_libraries(${TARGET_NAME} PUBLIC protobuf::libprotobuf)
target_include_directories(${TARGET_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")
protobuf_generate(TARGET ${TARGET_NAME})

# Generate Unit Tests
set(TARGET_NAME unit_tests)
add_executable(${TARGET_NAME} test_broker.cpp)
target_link_libraries(${TARGET_NAME}
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        pubsubservice_interface
        test_models
)