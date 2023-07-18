#include "proxyservice.h"
#include "mprpcapplication.h"
#include "proxyserver.pb.h"

using namespace std::placeholders;

ProxyService::ProxyService() : user_stub_(new rpc::MprpcChannel),
                               friendStub_(new rpc::MprpcChannel()),    
                               offlinemsgStub_(new rpc::MprpcChannel()),
                               grpStub_(new rpc::MprpcChannel())
{
    msg_handler_map_.insert({REG_MSG, bind(&ProxyService::Register, this, _1, _2, _3)});
    msg_handler_map_.insert({LOGIN_MSG, bind(&ProxyService::Login, this, _1, _2, _3)});
    msg_handler_map_.insert({LOGOUT_MSG, bind(&ProxyService::Logout, this, _1, _2, _3)});
    msg_handler_map_.insert({USERINFO_MSG, bind(&ProxyService::get_userInfo, this, _1, _2, _3)});
    msg_handler_map_.insert({ONE_CHAT_MSG, bind(&ProxyService::one_chat, this, _1, _2, _3)});
    msg_handler_map_.insert({GROUP_CHAT_MSG, bind(&ProxyService::group_chat, this, _1, _2, _3)});
    msg_handler_map_.insert({ADD_FRIEND_MSG, bind(&ProxyService::add_friend, this, _1, _2, _3)});
    msg_handler_map_.insert({DEL_FRIEND_MSG, bind(&ProxyService::delete_friend, this, _1, _2, _3)});
    msg_handler_map_.insert({CREATE_GROUP_MSG, bind(&ProxyService::create_group, this, _1, _2, _3)});
    msg_handler_map_.insert({JOIN_GROUP_MSG, bind(&ProxyService::join_group, this, _1, _2, _3)});
    msg_handler_map_.insert({QUIT_GROUP_MSG, bind(&ProxyService::quit_group, this, _1, _2, _3)});

    // 连接redis服务器
    string redisip = rpc::MprpcApplication::GetInstance().GetConfig().Load("redisip").c_str();
    int redisport = atoi(rpc::MprpcApplication::GetInstance().GetConfig().Load("redisport").c_str());
    if(_redis.connect(redisip, redisport)){
        // 设置上报消息的回调
        _redis.init_notify_handler(std::bind(&ProxyService::handleRedisSubscribeMessage, this, _1, _2));
    }
}
// 当监听的通道有消息时，意味着有转发而来的消息，再转发给客户端 √
void ProxyService::handleRedisSubscribeMessage(int userid, string msg){  
    proxyProto::ProxyRequest proxyReq;
    proxyReq.ParseFromString(msg);
    std::unique_lock<mutex> lock(mutex_);
    auto it = use_connection_map_.find(userid);
    if(it != use_connection_map_.end()){
        it->second->send(msg);
    }else{
        offlinemsgProto::WriteOfflineRequest woReq;
        offlinemsgProto::WriteOfflineReponse woRes;
        woReq.set_friendid(userid);
        woReq.set_msg(proxyReq.msg());
        offlinemsgStub_.WriteOffline(nullptr, &woReq, &woRes, nullptr);
    }
}

//获得消息对应的处理器 √
MsgHandler ProxyService::get_handler(int msg_type)
{
    //记录错误日志，msgid没有对应的事件处理回调
    auto it = msg_handler_map_.find(msg_type);
    //如果没有对应的msgid
    if (it == msg_handler_map_.end())
    {
        return [](const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time) {
            proxyProto::ProxyResponse proxyRes;
            proxyRes.set_type(PROXY_MSG_ACK);
            proxyRes.set_errcode(-1);
            proxyRes.set_errmsg("no handler!");
            conn->send(proxyRes.SerializeAsString());
        };
    }
    else
    {
        return msg_handler_map_[msg_type];
    }
}

//处理客户端异常退出 √
void ProxyService::client_close_exception(const rx::TcpConnectionPtr &conn)
{
    {
        lock_guard<mutex> lock(mutex_);
        for (auto it = use_connection_map_.begin(); it != use_connection_map_.end(); it++)
        {
            if (it->second == conn)
            {
                _redis.unsubscribe(it->first);
                use_connection_map_.erase(it);
                break;
            }
        }
    }
}

// 服务器退出，重置所有用户状态
void ProxyService::reset()
{
    usProto::LogoutRequest logoutRequest;
    usProto::LogoutResponse logoutResponse;
    proxyProto::ProxyRequest proxyReq;

    user_stub_.Logout(nullptr, &logoutRequest, &logoutResponse, nullptr);
    {
        lock_guard<mutex> lock(mutex_);
        //重置所有用户为下线状态
        for (auto it = use_connection_map_.begin(); it != use_connection_map_.end(); it++)
        {
            logoutRequest.set_userid(it->first);
            user_stub_.Logout(nullptr, &logoutRequest, &logoutResponse, nullptr);
            //在redis上删除用户
            _redis.unsubscribe(logoutRequest.userid());
            proxyReq.set_type(RESET_MSG_ACK);
            proxyReq.set_msg("server crash!");
            it->second->send(proxyReq.SerializeAsString());
        }
    }
    use_connection_map_.clear();
}

//注册
void ProxyService::Register(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time)
{
    //反序列化
    usProto::RegRequest regRequest;
    regRequest.ParseFromString(recv_buf);

    //执行
    usProto::RegResponse regResponse;
    user_stub_.Register(nullptr, &regRequest, &regResponse, nullptr);
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(PROXY_MSG_ACK);
    proxyRes.set_msg(regResponse.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}

// 登录
void ProxyService::Login(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time)
{
    //反序列化
    usProto::LoginRequest loginReq;
    loginReq.ParseFromString(recv_buf);

    //执行
    usProto::LoginResponse loginResponse;
    user_stub_.Login(nullptr, &loginReq, &loginResponse, nullptr);
    if(loginResponse.errcode() == 0){
        lock_guard<mutex> lock(mutex_);
        use_connection_map_.insert({loginReq.userid(), conn});
        _redis.subscribe(loginReq.userid());
    }
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(LOGIN_MSG_ACK);
    proxyRes.set_msg(loginResponse.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}

// 注销
void ProxyService::Logout(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time)
{
    usProto::LogoutRequest logoutRequest;
    logoutRequest.ParseFromString(recv_buf);
    usProto::LogoutResponse logoutResponse;
    user_stub_.Logout(nullptr, &logoutRequest, &logoutResponse, nullptr);
    if(logoutResponse.errcode() == 0){
        lock_guard<mutex> lock(mutex_);
        use_connection_map_.erase(logoutRequest.userid());
        _redis.unsubscribe(logoutRequest.userid());
    }
    conn->send(logoutResponse.SerializeAsString());
}

void ProxyService::one_chat(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time){
    proxyProto::ChatRequest chatReq;
    proxyProto::ChatResponse chatRes;

    chatReq.ParseFromString(recv_buf);
    int fromid = chatReq.fromid();
    int toid = chatReq.toid();

    friendProto::UserInfoRequest userinfoReq;
    userinfoReq.set_userid(toid);
    friendProto::UserInfoResponse userinfoRes;

    friendStub_.GetUserInfo(nullptr, &userinfoReq, &userinfoRes, nullptr);
    if(userinfoRes.errcode() != 0){
        chatRes.set_errcode(-1);
        chatRes.set_errmsg("get friend info fail，cant't send msg!");
    }
    if(userinfoRes.userinfo().state() == friendProto::OFFLINE){
        offlinemsgProto::WriteOfflineRequest woReq;
        offlinemsgProto::WriteOfflineReponse woRes;
        woReq.set_friendid(toid);
        woReq.set_msg(chatReq.msg());
        offlinemsgStub_.WriteOffline(nullptr, &woReq, &woRes, nullptr);
        if(woRes.errcode() != 0){
            chatRes.set_errcode(-1);
            chatRes.set_errmsg("Write Offlinemsg fail!");
        }
    }

    std::unique_lock<mutex> lock(mutex_);
    auto it = use_connection_map_.find(toid);
    if(it != use_connection_map_.end()){ // 客户端就连接在当前服务器, 直接转发
        it->second->send(chatReq.SerializeAsString());
    }else{ // 客户端连接到其他服务器上，向注册该通道的服务器发送消息
        proxyProto::ProxyRequest proxyReq;
        proxyReq.set_type(ONE_CHAT_MSG);
        proxyReq.set_msg(chatReq.SerializeAsString());
        _redis.publish(toid, proxyReq.SerializeAsString().c_str());
    }
    lock.unlock();
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(ONE_CHAT_MSG_ACK);
    proxyRes.set_msg(chatRes.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}


// 群组聊天业务
void ProxyService::group_chat(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time)
{
    proxyProto::ChatGroupequest chatgrpReq;
    chatgrpReq.ParseFromString(recv_buf);
    int fromid = chatgrpReq.fromid();
    int groupid = chatgrpReq.groupid();

    groupProto::QueryGroupUsersRequest qgrpusersReq;
    qgrpusersReq.set_userid(fromid);
    groupProto::QueryGroupUsersResponse qgrpusersRes;
    grpStub_.QueryGroupUsers(nullptr, &qgrpusersReq, &qgrpusersRes, nullptr);

    vector<int> toidVec(qgrpusersRes.useridvec().begin(), qgrpusersRes.useridvec().end());
    for(auto toid: toidVec){
        proxyProto::ChatRequest chatReq;
        chatReq.set_fromid(fromid);
        chatReq.set_toid(toid);
        chatReq.set_msg(chatgrpReq.msg());
        string msg = chatReq.SerializeAsString();
        one_chat(conn, msg, time);
    }
}


// 添加好友业务
void ProxyService::add_friend(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time){
    friendProto::AddFriendRequest addfriendReq;
    addfriendReq.ParseFromString(recv_buf);
    int userid = addfriendReq.userid();
    int friendid = addfriendReq.friendid();
    friendProto::AddFriendResponse addfriendRes;
    friendStub_.AddFriend(nullptr, &addfriendReq, &addfriendRes, nullptr);
    
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(ADD_FRIEND_MSG_ACK);
    proxyRes.set_msg(addfriendRes.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}

// 删除好友
void ProxyService::delete_friend(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time){
    friendProto::DelFriendRequest delfriendReq;
    delfriendReq.ParseFromString(recv_buf);
    int userid = delfriendReq.userid();
    int friendid = delfriendReq.friendid();
    friendProto::DelFriendResponse delfriendRes;
    friendStub_.DeleteFriend(nullptr, &delfriendReq, &delfriendRes, nullptr);
    
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(DEL_FRIEND_MSG_ACK);
    proxyRes.set_msg(delfriendRes.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}

//获取用户信息
void ProxyService::get_userInfo(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time){
    friendProto::UserInfoRequest userinfoReq;
    userinfoReq.ParseFromString(recv_buf);
    int userid = userinfoReq.userid();
    friendProto::UserInfoResponse userinfoRes;
    friendStub_.GetUserInfo(nullptr, &userinfoReq, &userinfoRes, nullptr);
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(USERINFO_MSG_ACK);
    proxyRes.set_msg(userinfoRes.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}

// 创建群组
void ProxyService::create_group(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time){
    groupProto::CreateGroupRequest createReq;
    createReq.ParseFromString(recv_buf);
    groupProto::CreateGroupResponse createRes;
    grpStub_.CreateGroup(nullptr, &createReq, &createRes, nullptr);
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(CREATE_GROUP_MSG_ACK);
    proxyRes.set_msg(createRes.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());

}

// 加入群组
void ProxyService::join_group(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time){
    groupProto::JoinGroupRequest joinReq;
    joinReq.ParseFromString(recv_buf);
    groupProto::JoinGroupResponse joinRes;
    grpStub_.JoinGroup(nullptr, &joinReq, &joinRes, nullptr);
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(JOIN_GROUP_MSG_ACK);
    proxyRes.set_msg(joinRes.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}

// 退出群
void ProxyService::quit_group(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time){
    groupProto::QuitGroupRequest quitReq;
    quitReq.ParseFromString(recv_buf);
    groupProto::QuitGroupResponse quitRes;
    grpStub_.QuitGroup(nullptr, &quitReq, &quitRes, nullptr);
    proxyProto::ProxyResponse proxyRes;
    proxyRes.set_type(QUIT_GROUP_MSG_ACK);
    proxyRes.set_msg(quitRes.SerializeAsString());
    conn->send(proxyRes.SerializeAsString());
}

