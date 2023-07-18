# aux_source_directory(. SRC_LIST)
set(SRC_LIST test.cpp ../src/proto/userService.pb.cc ../src/proto/proxyserver.pb.cc)
add_executable(test ${SRC_LIST})

target_link_libraries(test mprpc ReactorX ThreadPool pthread protobuf)
               