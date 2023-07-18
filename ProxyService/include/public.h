#ifndef PUBLIC_H
#define PUBLIC_H

/*
server和client的公共文件
*/
enum EnMsgType
{
    REG_MSG = 1, // 注册消息
    REG_MSG_ACK, // 注册响应消息

    LOGIN_MSG, // 登录消息
    LOGIN_MSG_ACK, // 登录响应消息

    LOGOUT_MSG, // 注销消息
    LOGOUT_MSG_ACK, // 注销响应消息
    
    USERINFO_MSG, //拉取用户信息消息
    USERINFO_MSG_ACK, // 拉取用户信息响应消息

    RESET_MSG_ACK, // 服务器重置消息

    ONE_CHAT_MSG, // 聊天消息
    ONE_CHAT_MSG_ACK, // 聊天响应消息

    GROUP_CHAT_MSG, // 群聊消息
    GROUP_CHAT_MSG_ACK, // 群聊响应消息

    ADD_FRIEND_MSG, // 添加好友消息
    ADD_FRIEND_MSG_ACK, // 添加好友响应消息

    DEL_FRIEND_MSG, // 删除好友消息
    DEL_FRIEND_MSG_ACK, // 删除好友响应消息

    CREATE_GROUP_MSG, // 创建群组消息
    CREATE_GROUP_MSG_ACK, // 创建群组响应消息

    JOIN_GROUP_MSG, // 加入群组消息
    JOIN_GROUP_MSG_ACK, // 加入群组响应消息

    QUIT_GROUP_MSG, // 退出群组消息
    QUIT_GROUP_MSG_ACK, // 退出群组响应消息
    
    PROXY_MSG_ACK // 代理层的响应消息

};

#endif