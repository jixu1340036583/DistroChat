#include "friendmodel.h"
#include "CommonConnectionPool.h"

bool FriendModel::insert(int userid, int friendid){
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into Friend(userid, friendid) values(%d, %d)", userid, friendid);
    
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    
    if(!conn->update(sql)){
        return false;
    }
    return true;
}


bool FriendModel::delFriend(int userid, int friendid){
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "detele from Friend where (userid = %d and friendid = %d) or (userid = %d and friendid = %d)", userid, friendid, friendid, userid);
    
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    
    if(!conn->update(sql)){
        return false;
    }
    return true;
}


bool FriendModel::query(int userid, vector<User>& vec){
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "SELECT u.userid, u.name, u.state FROM Friend f JOIN User u on f.friendid = u.userid where f.userid = %d;", userid);
    
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();

    MYSQL_RES *res = conn->query(sql);
    if(res != nullptr){
        MYSQL_ROW row;
        while((row = mysql_fetch_row(res)) != nullptr){
            User user;
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setState(row[2]);
            vec.push_back(std::move(user));
        }
        mysql_free_result(res);
    }
    
    return true;
}
