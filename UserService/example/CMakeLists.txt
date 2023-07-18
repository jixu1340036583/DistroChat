# aux_source_directory(. SRC_LIST)
set(SRC_LIST caller.cpp ../src/proto/userService.pb.cc)
add_executable(caller ${SRC_LIST})

target_link_libraries(caller mprpc ReactorX ThreadPool pthread protobuf)
               