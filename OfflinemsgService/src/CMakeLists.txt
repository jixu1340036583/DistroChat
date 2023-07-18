aux_source_directory(. SRC_LIST)
aux_source_directory(./proto PROTO_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./db DB_LIST)
add_executable(OfflinemsgService ${SRC_LIST} ${PROTO_LIST} ${MODEL_LIST} ${DB_LIST})

target_link_libraries(OfflinemsgService ConnectionPool mprpc ReactorX ThreadPool protobuf hiredis mysqlclient pthread)