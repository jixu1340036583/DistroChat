#include "usermodel.h"
#include "mprpcapplication.h"
#include "userService.pb.h"
#include "friendService.pb.h"
#include "groupService.pb.h"
#include "offlinemsgService.pb.h"

class UserService: public usProto::UserServiceRpc{
public:
    void Register(::google::protobuf::RpcController* controller,
                       const ::usProto::RegRequest* request,
                       ::usProto::RegResponse* response,
                       ::google::protobuf::Closure* done);
    void Login(::google::protobuf::RpcController* controller,
                       const ::usProto::LoginRequest* request,
                       ::usProto::LoginResponse* response,
                       ::google::protobuf::Closure* done);
    void Logout(::google::protobuf::RpcController* controller,
                       const ::usProto::LogoutRequest* request,
                       ::usProto::LogoutResponse* response,
                       ::google::protobuf::Closure* done);
private:
    UserModel userModel_;
    friendProto::FriendServiceRpc_Stub friendStub_ = new rpc::MprpcChannel();
    groupProto::GroupServiceRpc_Stub grpStub_ = new rpc::MprpcChannel();
    offlinemsgProto::OfflineServiceRpc_Stub offlinemsgStub_ = new rpc::MprpcChannel();
};