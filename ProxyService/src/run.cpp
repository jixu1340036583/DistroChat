#include <iostream>
#include <signal.h>
#include "mprpcapplication.h"
#include "TcpServer.h"
#include "proxyserver.h"
#include "proxyservice.h"

using namespace std;

// 服务器下线，重置所有用户的state
void reset_handler(int)
{
    ProxyService::getInstance().reset();
    exit(0);
}
int main(int argc, char **argv){
    rpc::MprpcApplication::Init(argc, argv);
    string ip = rpc::MprpcApplication::GetInstance().GetConfig().Load("proxyserverip").c_str();
    int port = atoi(rpc::MprpcApplication::GetInstance().GetConfig().Load("proxyserverport").c_str());

    // signal(SIGINT, reset_handler);

    //初始化zookeeper的连接
    // ProxyService::get_instance();
    
    rx::EventLoop loop;
    rx::InetAddress addr(port, ip);
    ProxyServer server(&loop, addr, "ProxyServer");

    server.start();
    loop.loop();

    return 0;

}