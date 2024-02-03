add_library(pubsubservice_models OBJECT pubsubservice.proto)
target_link_libraries(pubsubservice_models PUBLIC protobuf::libprotobuf)
target_include_directories(pubsubservice_models PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

protobuf_generate(TARGET pubsubservice_models)