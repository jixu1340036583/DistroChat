#include <iostream>
#include <string>
#include "FriendService.pb.h"

using namespace std;

int main(){
    /*
    cout<< "----------test regRequest ------------- " << endl;
    userServer::regRequest regreq;
    regreq.set_msgid(1);
    regreq.set_name("jixu");
    regreq.set_password("zxc");
    string send_str;
    const char* cs;
    if(regreq.SerializeToString(&send_str)){
        cs = send_str.c_str();
        cout<< cs << endl;
    }
    
    userServer::regRequest regreq_res;
    if(regreq_res.ParseFromString(send_str)){
        cout<< "msgid:" << regreq_res.msgid() << endl;
        cout<< "name:" << regreq_res.name() << endl;
        cout<< "password:" << regreq_res.password() << endl;
    }
    */
    cout<< "----------test LoginResponse ------------- " << endl;
    friendProto::LoginResponse loginres;
    loginres.set_msgid(1);
    loginres.set_errnum(0);
    loginres.set_userid(53);
    loginres.set_name("jixu");
    friendProto::User* user = loginres.add_friends();
    user->set_id(2);
    user->set_name("zou");
    user->set_password("yuhan");
    user->set_state(friendProto::User_STATE_online);
    for(int i = 0; i < 2; ++i){
        string* str = loginres.add_offlinemsg();
        *str = "hello";
    }


    string send_str;
    const char* cs;
    if(loginres.SerializeToString(&send_str)){
        cs = send_str.c_str();
        cout<< cs << endl;
    }
        friendProto::LoginResponse loginres_res;
    if(loginres_res.ParseFromString(send_str)){
        cout<< "msgid:" << loginres_res.msgid() << endl;
        cout<< "errnum:" << loginres_res.errnum() << endl;
        cout<< "errmsg:" << loginres_res.errmsg() << endl;
        cout<< "userid:" << loginres_res.userid() << endl;
        cout<< "name:" << loginres_res.name() << endl;
        int num = loginres_res.offlinemsg_size();
        cout<<"user.name:" << loginres_res.friends(0).name() << endl;
        cout<<"user.state:" << loginres_res.friends(0).state() << endl;
        for(int i = 0; i < num; ++i){
            cout<< "offlinemsg_size" << i <<":" << loginres_res.offlinemsg(i) << endl;
        }

    }
    



}