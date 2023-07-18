aux_source_directory(. SRC_LIST)
aux_source_directory(./proto PROTO_LIST)
aux_source_directory(./redis REDIS_LIST)

add_executable(ProxyService ${SRC_LIST} ${PROTO_LIST} ${REDIS_LIST})

target_link_libraries(ProxyService mprpc ReactorX ${LIBRARY_OUTPUT_PATH}/libThreadPool.so protobuf hiredis  pthread)