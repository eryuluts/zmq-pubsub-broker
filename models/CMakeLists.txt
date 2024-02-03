set(TARGET_NAME pubsubservice_models)
add_library(${TARGET_NAME} OBJECT pubsubservice.proto)
target_link_libraries(${TARGET_NAME} PUBLIC protobuf::libprotobuf)
target_include_directories(${TARGET_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

protobuf_generate(TARGET pubsubservice_models)