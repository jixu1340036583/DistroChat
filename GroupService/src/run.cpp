#include <iostream>
#include <signal.h>
#include "groupService.h"
#include "Logger.h"
#include "mprpcapplication.h"
#include "mprpcprovider.h"
// 处理服务器crtl+c结束后，重置user的状态信息
void resetHandler(int){
    // ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char **argv){
    rpc::MprpcApplication::Init(argc, argv);
    LOG_DEBUG("rpcserverip: %s", rpc::MprpcApplication::GetInstance().GetConfig().Load("rpcserverip").c_str());
    LOG_DEBUG("rpcserverport: %s", rpc::MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    LOG_DEBUG("zookeeperip: %s", rpc::MprpcApplication::GetInstance().GetConfig().Load("zookeeperip").c_str());
    LOG_DEBUG("zookeeperport: %s", rpc::MprpcApplication::GetInstance().GetConfig().Load("zookeeperport").c_str());
    rpc::MpRpcProvider provider;
    provider.NotifyService(new GroupService());
    provider.Run();
    return 0;
}