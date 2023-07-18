#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.h"
#include <string>
#include <vector>
using namespace std;

// 维护群组信息的操作接口方法
class GroupModel
{
public:
    // 创建群组
    bool createGroup(Group &group);
    // 加入群组
    bool joinGroup(int userid, int groupid, string role);
    bool quitGroup(int userid, int groupid);
    // 查询用户所在群组信息
    bool queryGroups(int userid, vector<Group>& groupVec);
    // 根据指定的groupid查询群组用户id列表，（不返回userid自己），用于用户给某个群组其他成员群发消息
    bool queryGroupUsers(int userid, int groupid, vector<int>& useridVec);
};

#endif