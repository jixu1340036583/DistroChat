#ifndef PUBLIC_H
#define PUBLIC_H

/*
server和client的公共文件
*/
enum EnMsgType
{

    USERINFO_MSG, // 获取用户信息消息
    USERINFO_MSG_ACK, // 获取用户信息响应消息

    ADD_FRIEND_MSG, // 添加好友消息
    ADD_FRIEND_MSG_ACK, // 添加好友响应消息

    DEL_FRIEND_MSG, // 删除好友消息
    DEL_FRIEND_MSG_ACK, // 删除好友响应消息

    FRIENDLIST_MSG, // 获取好友列表消息
    FRIENDLIST_MSG_ACK, // 获取好友列表响应消息
   
};

#endif