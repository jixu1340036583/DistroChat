#pragma once
#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <mutex>
#include "TcpServer.h"
#include "public.h"
#include "redis.h"
#include "friendService.pb.h"
#include "userService.pb.h"
#include "offlinemsgService.pb.h"
#include "groupService.pb.h"
using MsgHandler = std::function<void(const rx::TcpConnectionPtr &conn, std::string &recv_str, Timestamp time)>;

//单例设计
class ProxyService
{
public:
    static ProxyService &getInstance()
    {
        static ProxyService service;
        return service;
    }

    void Register(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time); // 注册 √

    void Login(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time); // 登录 √
    
    void Logout(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time); // 下线 √

    MsgHandler get_handler(int msg_type); // 获得消息对应的处理器 √

    void client_close_exception(const rx::TcpConnectionPtr &conn); // 处理客户端异常退出 √

    void reset(); // 服务器异常，业务重置 √
    // redis订阅通道收到消息的回调函数。 当监听的通道有消息时，意味着有转发而来的消息，再转发给客户端 √
    void handleRedisSubscribeMessage(int userid, std::string msg); 

    // 一对一聊天业务 √
    void one_chat(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time); 

    // 一对一聊天业务 √
    void group_chat(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time); 

    // 添加好友业务 √
    void add_friend(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time);

    // 删除好友
    void delete_friend(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time);

    // 获取用户信息
    void get_userInfo(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time);

    // 创建群组
    void create_group(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time);

    // 加入群组
    void join_group(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time);

    // 退出群
    void quit_group(const rx::TcpConnectionPtr &conn, std::string &recv_buf, Timestamp time);


private:
    ProxyService();


    ProxyService(const ProxyService &) = delete;
    ProxyService &operator=(ProxyService &) = delete;


    std::unordered_map<int, MsgHandler> msg_handler_map_; //存储事件及事件对应的回调函数

    std::unordered_map<int, rx::TcpConnectionPtr> use_connection_map_; //存储登录用户，及对应tcpptr信息
    std::mutex mutex_;                                                         //保护上一个的线程安全

    // redis 操作对象
    Redis _redis;

    //ZKMatser master_; //连接zookeeper服务器

    usProto::UserServiceRpc_Stub user_stub_;
    friendProto::FriendServiceRpc_Stub friendStub_;
    offlinemsgProto::OfflineServiceRpc_Stub offlinemsgStub_;
    groupProto::GroupServiceRpc_Stub grpStub_;
};