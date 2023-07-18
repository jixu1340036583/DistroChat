#ifndef USERSERVER_H
#define USERSERVER_H
/*
muduo网络库给用户提供了两个主要的类
TcpServer ： 用于编写服务器程序的
TcpClient ： 用于编写客户端程序的

epoll + 线程池
使用网络库的好处：能够把网络I/O(用户的连接和断开)的代码和业务(用户的可读写事件)代码区分开
                   
*/
#include <TcpServer.h>
#include <EventLoop.h>


// 聊天服务器的主类
class ProxyServer
{
public:
    // 初始化聊天服务器对象
    ProxyServer(rx::EventLoop *loop,
               const rx::InetAddress &listenAddr,
               const std::string &nameArg);

    // 启动服务
    void start();

private:
    // 上报链接相关信息的回调函数
    void onConnection(const rx::TcpConnectionPtr &);

    // 上报读写事件相关信息的回调函数
    void onMessage(const rx::TcpConnectionPtr &,
                   rx::Buffer *,
                   Timestamp);

    rx::TcpServer _server; 
    rx::EventLoop *_loop;  
};

#endif
