#include "groupmodel.h"
#include "CommonConnectionPool.h"
// 创建群组
bool GroupModel::createGroup(Group &group)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into AllGroup(groupname, groupdesc) values('%s', '%s');",
            group.getName().c_str(), group.getDesc().c_str());

    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    
    if(conn->update(sql)){
        group.setId(mysql_insert_id(conn->getConnection()));
        return true;
    }
    return false;
}

// 加入群组
bool GroupModel::joinGroup(int userid, int groupid, string role)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into GroupUser values(%d, %d, '%s');",
            groupid, userid, role.c_str());

    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    
    if(!conn->update(sql)){
        return false;
    }
    return true;
}

bool GroupModel::quitGroup(int userid, int groupid){
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "delete from GroupUser where groupid=%d and userid=%d;",
            groupid, userid);

    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    
    if(!conn->update(sql)){
        return false;
    }
    return true;
}


// 查询用户所在群组信息
bool GroupModel::queryGroups(int userid, vector<Group>& groupVec)
{
    /*
    1. 先根据userid在groupuser表中查询出该用户所属的群组信息
    2. 在根据群组信息，查询属于该群组的所有用户的userid，并且和user表进行多表联合查询，查出用户的详细信息
    */
    char sql[1024] = {0};
    sprintf(sql, "select al.groupid,al.groupname,al.groupdesc from AllGroup al join GroupUser gu using(groupid) where gu.userid=%d;",
            userid);

    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();

    MYSQL_RES *res = conn->query(sql);
    if (res == nullptr)
    {
        MYSQL_ROW row;
        // 查出userid所有的群组信息
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            Group group;
            group.setId(atoi(row[0]));
            group.setName(row[1]);
            group.setDesc(row[2]);
            groupVec.push_back(std::move(group));
        }
        mysql_free_result(res);
    }

    

    // 查询群组的用户信息
    for (Group &group : groupVec)
    {
        sprintf(sql, "select u.userid, u.name, u.state, gu.grouprole from User u join GroupUser gu using(userid) where gu.groupid = %d;",
                group.getId());

        MYSQL_RES *res = conn->query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                GroupUser user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                user.setRole(row[3]);
                group.getUsers().push_back(std::move(user));
            }
            mysql_free_result(res);
        }
    }
    return true;

}

// 根据指定的groupid查询群组用户id列表，（不返回userid自己），用于用户给某个群组其他成员群发消息
bool GroupModel::queryGroupUsers(int userid, int groupid, vector<int>& useridVec)
{
    char sql[1024] = {0};
    sprintf(sql, "select userid from GroupUser where groupid = %d and userid != %d;", groupid, userid);

    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();

    MYSQL_RES *res = conn->query(sql);
    if (res != nullptr)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != nullptr)
        {
            useridVec.push_back(atoi(row[0]));
        }
        mysql_free_result(res);
    }
    return true;
}