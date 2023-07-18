#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H
#include <vector>
#include "user.h"
using namespace std;
class FriendModel{
public:
    // 添加好友
    bool insert(int userid, int friendid);
    // 删除好友
    bool delFriend(int userid, int friendid);
    // 当用户登录时，返回该用户的好友列表
    bool query(int userid, vector<User>& vec);

};



#endif