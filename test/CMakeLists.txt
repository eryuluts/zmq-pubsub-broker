include(GoogleTest)

set(TARGET_NAME unit_tests)
add_executable(${TARGET_NAME} broker.cpp)
target_link_libraries(${TARGET_NAME}
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)

gtest_add_tests(TARGET ${TARGET_NAME})
