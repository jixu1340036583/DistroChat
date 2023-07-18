#include "offlinemsgService.pb.h"
#include "offlinemessagemodel.h"

class OfflinemsgService: public offlinemsgProto::OfflineServiceRpc{
public:
    void WriteOffline(::google::protobuf::RpcController* controller,
                       const ::offlinemsgProto::WriteOfflineRequest* request,
                       ::offlinemsgProto::WriteOfflineReponse* response,
                       ::google::protobuf::Closure* done);
    void ReadOffline(::google::protobuf::RpcController* controller,
                       const ::offlinemsgProto::ReadOfflineRequest* request,
                       ::offlinemsgProto::ReadOfflineResponse* response,
                       ::google::protobuf::Closure* done);
    void DelOffline(::google::protobuf::RpcController* controller,
                       const ::offlinemsgProto::ReadOfflineRequest* request,
                       ::offlinemsgProto::DelOfflineResponse* response,
                       ::google::protobuf::Closure* done);
private:
    OfflineMessageModel offlinemsgModel_;
};