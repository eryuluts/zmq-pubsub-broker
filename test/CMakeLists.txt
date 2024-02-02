include(GoogleTest)

set(TARGET_NAME unit_tests)
add_executable(${TARGET_NAME} test_broker.cpp)
target_link_libraries(${TARGET_NAME}
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)