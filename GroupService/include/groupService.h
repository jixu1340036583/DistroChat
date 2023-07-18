#include "groupService.pb.h"
#include "groupmodel.h"
class GroupService: public groupProto::GroupServiceRpc{
public:
    void CreateGroup(::google::protobuf::RpcController* controller,
                       const ::groupProto::CreateGroupRequest* request,
                       ::groupProto::CreateGroupResponse* response,
                       ::google::protobuf::Closure* done);
    void JoinGroup(::google::protobuf::RpcController* controller,
                       const ::groupProto::JoinGroupRequest* request,
                       ::groupProto::JoinGroupResponse* response,
                       ::google::protobuf::Closure* done);
    void QuitGroup(::google::protobuf::RpcController* controller,
                       const ::groupProto::QuitGroupRequest* request,
                       ::groupProto::QuitGroupResponse* response,
                       ::google::protobuf::Closure* done);
    void QueryGroups(::google::protobuf::RpcController* controller,
                       const ::groupProto::QueryGroupsRequest* request,
                       ::groupProto::QueryGroupsResponse* response,
                       ::google::protobuf::Closure* done);
    void QueryGroupUsers(::google::protobuf::RpcController* controller,
                       const ::groupProto::QueryGroupUsersRequest* request,
                       ::groupProto::QueryGroupUsersResponse* response,
                       ::google::protobuf::Closure* done);

    
private:
    GroupModel groupModel_;
};