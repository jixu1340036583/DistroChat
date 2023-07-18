#include <string>
#include "public.h"
#include "friendService.h"

#include "usermodel.h"

void FriendService::GetUserInfo(::google::protobuf::RpcController* controller,
                    const ::friendProto::UserInfoRequest* request,
                    ::friendProto::UserInfoResponse* response,
                    ::google::protobuf::Closure* done){
    int userid = request->userid();
    User user = userModel_.query(userid);
    if(user.getId() != -1){
        response->set_errcode(0);
        friendProto::User* userRes = response->mutable_userinfo();
        userRes->set_id(user.getId());
        userRes->set_name(user.getName());
        userRes->set_password(user.getPwd());
        userRes->set_state(user.getState() == string("online") ? friendProto::ONLINE : friendProto::OFFLINE);
    }
    else{
        response->set_errcode(-1);
        response->set_errmsg("查询用户id为：%d的信息失败！", userid);
    }
    done->Run();
    
}
void FriendService::AddFriend(::google::protobuf::RpcController* controller,
                    const ::friendProto::AddFriendRequest* request,
                    ::friendProto::AddFriendResponse* response,
                    ::google::protobuf::Closure* done){
    int userid = request->userid();
    int friendid = request->friendid();
    friendModel_.insert(userid, friendid);
    done->Run();
}

void FriendService::DeleteFriend(::google::protobuf::RpcController* controller,
                    const ::friendProto::DelFriendRequest* request,
                    ::friendProto::DelFriendResponse* response,
                    ::google::protobuf::Closure* done){
    int userid = request->userid();
    int friendid = request->friendid();
    friendModel_.delFriend(userid, friendid);
    done->Run();
}
void FriendService::GetFriendList(::google::protobuf::RpcController* controller,
                    const ::friendProto::FriendListRequest* request,
                    ::friendProto::FriendListResponse* response,
                    ::google::protobuf::Closure* done){
    int userid = request->userid();
    vector<User> userVec;
    if(!friendModel_.query(userid, userVec)){
        response->set_errcode(-1);
        response->set_errmsg("获取用户好友列表失败！");
    }
    for(int i = 0; i < userVec.size(); ++i){
        friendProto::User* user = response->add_friendlist();
        user->set_id(userVec[i].getId());
        user->set_name(userVec[i].getName());
        user->set_state(userVec[i].getState() == "online" ? friendProto::ONLINE : friendProto::OFFLINE);
    }
    done->Run();
}