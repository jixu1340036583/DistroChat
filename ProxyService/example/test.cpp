#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "proxyserver.pb.h"
#include "userService.pb.h"
#include "public.h"
#include "Logger.h"


int test_register(){
    // rpc方法的请求参数
    usProto::RegRequest regRequest;
    regRequest.set_name("zhang san");
    regRequest.set_password("123456");

    proxyProto::ProxyRequest proxyReq;
    proxyReq.set_type(REG_MSG);
    proxyReq.set_msg(regRequest.SerializeAsString());
    std::string send_str = proxyReq.SerializeAsString();

    std::string ip = "127.0.0.1";
    uint16_t port = 8000;

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1){
        char errtxt[512] = {0};
        sprintf(errtxt, "create socket error! errno: %d", errno);
        return -1;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    // 连接rpc服务节点
    if(-1 == connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr))){
        char errtxt[512] = {0};
        sprintf(errtxt, "connect error! errno: %d", errno);
        close(clientfd);
        return -1;
    }

    // 发送rpc请求
    if(-1 == send(clientfd, send_str.c_str(), send_str.size(), 0)){
        char errtxt[512] = {0};
        sprintf(errtxt, "send error! errno: %d", errno);
        close(clientfd);
        return -1;
    }

    // 接收rpc请求的响应值
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if(-1 == (recv_size = recv(clientfd, recv_buf, 1024, 0))){
        char errtxt[512] = {0};
        sprintf(errtxt, "receive error! errno: %d", errno);
        close(clientfd);
        return -1;
    }

    // rpc方法的响应
    proxyProto:: ProxyResponse proxyRes;
    usProto::RegResponse regResponse;

    // std::string response_str(recv_buf, 0, recv_size); // 这里有个bug, recv_buf中遇到\0后面的数据就存不下来了！！！
    // !!!!!!!!!!!!!!!!!!这里要好好总结，为什么会有/n？？？？学习学习调试
    if(!proxyRes.ParseFromArray(recv_buf, recv_size)){
        char errtxt[1050] = {0};
        sprintf(errtxt, "parse error! respnse_str: %s", recv_buf);
        close(clientfd);
        return -1;
    }
    if(proxyRes.errcode() != 0){
        LOG_ERROR("Register fail!");
        LOG_ERROR("errmsg:%s", proxyRes.errmsg().c_str());
    }
    else{
        regResponse.ParseFromString(proxyRes.msg());
        LOG_INFO("Register success!");
        LOG_INFO("name: %s", regRequest.name().c_str());
        LOG_INFO("new userid: %d", regResponse.userid());
    
    }
    return 0;
}

int test_login(){
    // rpc方法的请求参数
    usProto::LoginRequest loginRequest;
    loginRequest.set_userid(123);
    loginRequest.set_password("zxc");

    proxyProto::ProxyRequest proxyReq;
    proxyReq.set_type(LOGIN_MSG);
    proxyReq.set_msg(loginRequest.SerializeAsString());
    std::string send_str = proxyReq.SerializeAsString();

    std::string ip = "127.0.0.1";
    uint16_t port = 8000;

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1){
        char errtxt[512] = {0};
        sprintf(errtxt, "create socket error! errno: %d", errno);
        return -1;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    // 连接rpc服务节点
    if(-1 == connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr))){
        char errtxt[512] = {0};
        sprintf(errtxt, "connect error! errno: %d", errno);
        close(clientfd);
        return -1;
    }

    // 发送rpc请求
    if(-1 == send(clientfd, send_str.c_str(), send_str.size(), 0)){
        char errtxt[512] = {0};
        sprintf(errtxt, "send error! errno: %d", errno);
        close(clientfd);
        return -1;
    }

    // 接收rpc请求的响应值
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if(-1 == (recv_size = recv(clientfd, recv_buf, 1024, 0))){
        char errtxt[512] = {0};
        sprintf(errtxt, "receive error! errno: %d", errno);
        close(clientfd);
        return -1;
    }

    // rpc方法的响应
    proxyProto:: ProxyResponse proxyRes;
    usProto::LoginResponse loginRes;

    // std::string response_str(recv_buf, 0, recv_size); // 这里有个bug, recv_buf中遇到\0后面的数据就存不下来了！！！
    // !!!!!!!!!!!!!!!!!!这里要好好总结，为什么会有/n？？？？学习学习调试
    if(!proxyRes.ParseFromArray(recv_buf, recv_size)){
        char errtxt[1050] = {0};
        sprintf(errtxt, "parse error! respnse_str: %s", recv_buf);
        close(clientfd);
        return -1;
    }
    if(proxyRes.errcode() != 0){
        LOG_ERROR("errmsg:%s", proxyRes.errmsg().c_str());
    }
    else{
        loginRes.ParseFromString(proxyRes.msg());
        if(loginRes.errcode() != 0) LOG_INFO("Login fail!, errcode:%d, errmsg:%s", loginRes.errcode(), loginRes.errmsg().c_str());
        else{
            LOG_INFO("Login success!");
            // 输出好友、群组、群友
        }
    }
    return 0;
}


int main(int argc, char** argv){
    //test_register();
    test_login();
    return 0;
}