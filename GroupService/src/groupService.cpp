#include <string>
#include "public.h"
#include "groupService.h"

void GroupService::CreateGroup(::google::protobuf::RpcController* controller,
                       const ::groupProto::CreateGroupRequest* request,
                       ::groupProto::CreateGroupResponse* response,
                       ::google::protobuf::Closure* done){
    Group group(request->group_name(), request->group_desc());
    if(groupModel_.createGroup(group)){
        response->set_errcode(0);
        response->set_groupid(group.getId());
    }
    else{
        response->set_errcode(-1);
        response->set_errmsg("CreateGroup fail!");
    }           
    done->Run();
}
void GroupService::JoinGroup(::google::protobuf::RpcController* controller,
                    const ::groupProto::JoinGroupRequest* request,
                    ::groupProto::JoinGroupResponse* response,
                    ::google::protobuf::Closure* done){
    int userid = request->userid();
    int groupid = request->groupid();
    std::string role = request->role() == groupProto::CREATOR ? "creator" : "normal";
    if(groupModel_.joinGroup(userid, groupid, role)){
        response->set_errcode(0);
    }else{
        response->set_errcode(-1);
        response->set_errmsg("JoinGroup fail!");
    }
    done->Run();
}
void GroupService::QuitGroup(::google::protobuf::RpcController* controller,
                    const ::groupProto::QuitGroupRequest* request,
                    ::groupProto::QuitGroupResponse* response,
                    ::google::protobuf::Closure* done){
    int userid = request->userid();
    int groupid = request->groupid();
    if(groupModel_.quitGroup(userid, groupid)){
        response->set_errcode(0);
    }else{
        response->set_errcode(-1);
        response->set_errmsg("QuitGroup fail!");
    }
    done->Run();
}
void GroupService::QueryGroups(::google::protobuf::RpcController* controller,
                       const ::groupProto::QueryGroupsRequest* request,
                       ::groupProto::QueryGroupsResponse* response,
                       ::google::protobuf::Closure* done){
    int userid = request->userid();
    std::vector<Group> groupVec;
    if(groupModel_.queryGroups(userid, groupVec)){
        response->set_errcode(0);
        for(int i = 0; i < groupVec.size(); ++i){
            groupProto::Group* group = response->add_groups();
            for(int j = 0; j < groupVec[i].getUsers().size(); ++i){
                groupProto::GroupUser* guser = group->add_users();
                guser->set_id(groupVec[i].getUsers()[j].getId());
                guser->set_name(groupVec[i].getUsers()[j].getName());
                guser->set_state(groupVec[i].getUsers()[j].getState() == "online" ? groupProto::ONLINE : groupProto::OFFLINE);
                guser->set_role(groupVec[i].getUsers()[j].getRole() == "creator" ? groupProto::CREATOR : groupProto::NORMAL);
            }
        }
    }
    else{
        response->set_errcode(-1);
        response->set_errmsg("QueryGroups fail!");
    }
    done->Run();
}

void GroupService::QueryGroupUsers(::google::protobuf::RpcController* controller,
                       const ::groupProto::QueryGroupUsersRequest* request,
                       ::groupProto::QueryGroupUsersResponse* response,
                       ::google::protobuf::Closure* done){
    int userid = request->userid();
    int groupid = request->groupid();
    vector<int> useridVec;
    if(groupModel_.queryGroupUsers(userid, groupid, useridVec)){
        response->set_errcode(0);
        for(int i = 0; i < useridVec.size(); ++i){
            response->add_useridvec(useridVec[i]);
        }
    }
    else{
        response->set_errcode(-1);
        response->set_errmsg("QueryGroups fail!");
    }
    done->Run();
}
