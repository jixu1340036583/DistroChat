#include "offlinemessagemodel.h"
#include "CommonConnectionPool.h"

bool OfflineMessageModel::insert(int userid, string msg){
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into OfflineMessage(userid, message) values(%d, '%s');", userid, msg.c_str());
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    if(conn->update(sql)){
        return true;
    }
    return false;
}

bool OfflineMessageModel::remove(int userid){
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "delete from OfflineMessage where userid = %d;", userid);
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    if(conn->update(sql)){
        return true;
    }
    return false;
}

// 查询离线消息
bool OfflineMessageModel::query(int userid, vector<string>& vec){
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select message from OfflineMessage where userid = %d;", userid);

    
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    MYSQL_RES* res = conn->query(sql);
    if(res != nullptr){
        MYSQL_ROW row;
        while((row = mysql_fetch_row(res)) != nullptr){
            vec.push_back(row[0]);
        }
        mysql_free_result(res);
    }
    
    return true;
}