#include <string>
#include "public.h"
#include "offlinemsgService.h"


void OfflinemsgService::WriteOffline(::google::protobuf::RpcController* controller,
                       const ::offlinemsgProto::WriteOfflineRequest* request,
                       ::offlinemsgProto::WriteOfflineReponse* response,
                       ::google::protobuf::Closure* done){
    int friendid = request->friendid();
    if(offlinemsgModel_.insert(friendid, request->msg())){
        response->set_errcode(0);
    }else{
        response->set_errmsg("WriteOffline fail!");
        response->set_errcode(-1);
    }
    done->Run();

}
void OfflinemsgService::ReadOffline(::google::protobuf::RpcController* controller,
                       const ::offlinemsgProto::ReadOfflineRequest* request,
                       ::offlinemsgProto::ReadOfflineResponse* response,
                       ::google::protobuf::Closure* done){
    int userid = request->userid();  
    
    vector<string> msgVec;
    if(!offlinemsgModel_.query(userid, msgVec)){
        response->set_errcode(-1);
        response->set_errmsg("ReadOffline fail!");
    }
    for(int i = 0; i < msgVec.size(); ++i){
        string* msg = response->add_msg();
        *msg = std::move(msgVec[i]);
    }
    done->Run();
}

void OfflinemsgService::DelOffline(::google::protobuf::RpcController* controller,
                       const ::offlinemsgProto::ReadOfflineRequest* request,
                       ::offlinemsgProto::DelOfflineResponse* response,
                       ::google::protobuf::Closure* done){
    int userid = request->userid();
    if(!offlinemsgModel_.remove(userid)){
        response->set_errcode(-1);
        response->set_errmsg("DelOffline fail!");
    }
    response->set_errcode(0);
    done->Run();
}
