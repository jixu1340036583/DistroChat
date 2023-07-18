#include <iostream>
#include "groupService.pb.h"
#include "mprpcapplication.h"
#include "public.h"
#include "Logger.h"
int main(int argc, char** argv){
    rpc::MprpcApplication::Init(argc, argv);
    // 演示调用远程发布的rpc方法Login
    groupProto::GroupServiceRpc_Stub stub(new rpc::MprpcChannel());
    // // rpc方法的请求参数
    // groupProto::RegRequest request;
    // request.set_name("zhang san");
    // request.set_password("123456");
    // // rpc方法的响应
    // groupProto::RegResponse response;

    // // 发起rpc方法的调用，同步的rpc调用过程 MprpcChannel::Callmethod
    // rpc::MprpcController controller;
    // stub.Register(&controller, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用参数序列化和网络发送
    
    // // 一次rpc调用完成，读调用的结果

    // if(controller.Failed()){ // rpc调用出错了
    //     std::cout << controller.ErrorText() << std::endl;
    // }else{
    //     if(response.errcode() == 0){
    //         LOG_INFO("rpc login success!");
    //         LOG_INFO("new userid:%d", response.userid());
    //     }
    //     else{
    //         LOG_INFO("rpc login fail!");
    //         LOG_INFO("rpc login response error:%s", response.errmsg().c_str());
    //     }   
            
    // }
    
    return 0;
}