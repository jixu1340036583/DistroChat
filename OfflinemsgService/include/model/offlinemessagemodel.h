#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H
#include <string>
#include <vector>
using std::string;
using std::vector;
// 提供离线消息表的操作接口方法
class OfflineMessageModel
{
private:
    /* data */
public:
    // 存储用户的离线消息
    bool insert(int userid, string msg);
    
    // 删除用户的离线消息
    bool remove(int userid);

    // 查询用户的离线消息
    bool query(int userid, vector<string>&);
    

};





#endif