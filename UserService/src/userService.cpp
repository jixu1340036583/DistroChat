#include <string>
#include "public.h"
#include "userService.h"
void UserService::Register(::google::protobuf::RpcController* controller,
                       const ::usProto::RegRequest* request,
                       ::usProto::RegResponse* response,
                       ::google::protobuf::Closure* done){
    std::string name = request->name();
    std::string pwd = request->password();

    User user;
    user.setName(name);
    user.setPwd(pwd);
    bool state = userModel_.insert(user);
    if(state){
        response->set_errcode(0);
        response->set_userid(user.getId());
    }
    else{
        response->set_errcode(-1);
        response->set_errmsg("register fail!");
    }
    done->Run();
}

void UserService::Login(::google::protobuf::RpcController* controller,
                       const ::usProto::LoginRequest* request,
                       ::usProto::LoginResponse* response,
                       ::google::protobuf::Closure* done){
    int userid = request->userid();
    std::string pwd = request->password();

    friendProto::UserInfoRequest userinfoReq;
    userinfoReq.set_userid(userid);
    friendProto::UserInfoResponse userinfoRes;
    friendStub_.GetUserInfo(nullptr, &userinfoReq, &userinfoRes, nullptr);
    if(userinfoRes.errcode() != 0){
        response->set_errcode(-1);
        response->set_errmsg(userinfoRes.errmsg());
    }
    if(userinfoRes.userinfo().password() != pwd){
        response->set_errcode(-1);
        response->set_errmsg("password is wrong!");
    }
    if(userinfoRes.userinfo().state() == friendProto::ONLINE){
        response->set_errcode(-1);
        response->set_errmsg("the user is Online!");
    }
    friendProto::FriendListRequest friendListReq;
    friendProto::FriendListResponse friendListRes;
    friendStub_.GetFriendList(nullptr, &friendListReq, &friendListRes, nullptr);
    if(friendListRes.errcode() != 0){
        response->set_errcode(-1);
        response->set_errmsg(friendListRes.errmsg());
    }
    for(int i = 0; i < friendListRes.friendlist_size(); ++i){
        usProto::User* user = response->add_friends();
        user->set_id(friendListRes.friendlist(i).id());
        user->set_name(friendListRes.friendlist(i).name());
        user->set_state(friendListRes.friendlist(i).state() == friendProto::ONLINE ? usProto::ONLINE : usProto::OFFLINE);
    }

    groupProto::QueryGroupsRequest qgrpReq;
    qgrpReq.set_userid(userid);
    groupProto::QueryGroupsResponse qgrpRes;
    grpStub_.QueryGroups(nullptr, &qgrpReq, &qgrpRes, nullptr);

    if(qgrpRes.errcode() != 0){
        response->set_errcode(-1);
        response->set_errmsg(qgrpRes.errmsg());
    }
    for (size_t i = 0; i < qgrpRes.groups_size(); i++)
    {
        usProto::Group* grp = response->add_groups();
        grp->set_groupid(qgrpRes.groups(i).groupid());
        grp->set_name(qgrpRes.groups(i).name());
        grp->set_desc(qgrpRes.groups(i).desc());
        for(int j = 0; j < qgrpRes.groups(i).users_size(); ++j){
            usProto::GroupUser* guser = grp->add_users();
            guser->set_id(qgrpRes.groups(i).users(j).id());
            guser->set_name(qgrpRes.groups(i).users(j).name());
            guser->set_state(qgrpRes.groups(i).users(j).state() == groupProto::ONLINE ? usProto::ONLINE : usProto::OFFLINE);
            guser->set_role(qgrpRes.groups(i).users(j).role() == groupProto::CREATOR ? usProto::CREATOR : usProto::NORMAL);
        }
    }

    offlinemsgProto::ReadOfflineRequest roReq;
    roReq.set_userid(userid);
    offlinemsgProto::ReadOfflineResponse roRes;
    offlinemsgStub_.ReadOffline(nullptr, &roReq, &roRes, nullptr);
    if(roRes.errcode() != 0){
        response->set_errcode(-1);
        response->set_errmsg(roRes.errmsg());
    }
    for(int i = 0; i < roRes.msg_size(); ++i){
        response->add_offlinemsg(roRes.msg(i).c_str());
    }
    done->Run(); 

                    
}
void UserService::Logout(::google::protobuf::RpcController* controller,
                       const ::usProto::LogoutRequest* request,
                       ::usProto::LogoutResponse* response,
                       ::google::protobuf::Closure* done){
    int userid = request->userid();
    if(userModel_.updateState(userid, "offline")){
        response->set_errcode(-1);
        response->set_errmsg("Logout fail!");
    }
    done->Run();
}

