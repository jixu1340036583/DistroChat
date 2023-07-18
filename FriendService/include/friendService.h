#include "friendService.pb.h"
#include "usermodel.h"
#include "friendmodel.h"
class FriendService: public friendProto::FriendServiceRpc{
public:
    void GetUserInfo(::google::protobuf::RpcController* controller,
                       const ::friendProto::UserInfoRequest* request,
                       ::friendProto::UserInfoResponse* response,
                       ::google::protobuf::Closure* done);
    void AddFriend(::google::protobuf::RpcController* controller,
                       const ::friendProto::AddFriendRequest* request,
                       ::friendProto::AddFriendResponse* response,
                       ::google::protobuf::Closure* done);
    void DeleteFriend(::google::protobuf::RpcController* controller,
                       const ::friendProto::DelFriendRequest* request,
                       ::friendProto::DelFriendResponse* response,
                       ::google::protobuf::Closure* done);
    void GetFriendList(::google::protobuf::RpcController* controller,
                       const ::friendProto::FriendListRequest* request,
                       ::friendProto::FriendListResponse* response,
                       ::google::protobuf::Closure* done);
private:
    UserModel userModel_;
    FriendModel friendModel_;
};