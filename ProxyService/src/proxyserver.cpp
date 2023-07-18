#include <iostream>
#include <functional>
#include <string>
#include "proxyserver.h"
#include "proxyservice.h"
#include "proxyserver.pb.h"
#include "Logger.h"

using namespace std;
using namespace placeholders;

// 初始化聊天服务器对象
ProxyServer::ProxyServer(rx::EventLoop *loop,
                       const rx::InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册链接回调
    _server.setConnectionCallback(std::bind(&ProxyServer::onConnection, this, _1));

    // 注册消息回调
    _server.setMessageCallback(std::bind(&ProxyServer::onMessage, this, _1, _2, _3));

    // 设置线程数量
    _server.setLoopNum(4);
}

// 启动服务
void ProxyServer::start()    
{
    _server.start();
}

// 上报链接相关信息的回调函数
void ProxyServer::onConnection(const rx::TcpConnectionPtr &conn)
{
    // 客户端断开链接
    if (!conn->connected())
    {
        ProxyService::getInstance().client_close_exception(conn);
        conn->shutdown();
    }
}

// 上报读写事件相关信息的回调函数
void ProxyServer::onMessage(const rx::TcpConnectionPtr &conn,
                           rx::Buffer *buffer,
                           Timestamp time)
{
    string recv_str = buffer->retrieveAllAsString();
    proxyProto::ProxyRequest request;
    request.ParseFromString(recv_str);
    auto msg_handler = ProxyService::getInstance().get_handler(request.type());
    string str = request.msg();
    msg_handler(conn, str, time);
    return;
}

