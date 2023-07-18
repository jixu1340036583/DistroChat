#include <iostream>
#include "usermodel.h"
#include "CommonConnectionPool.h"
bool UserModel::insert(User &user){
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into User(name, password, state) values('%s', '%s', '%s')", \
    user.getName().c_str(), user.getPwd().c_str(), user.getState().c_str());
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();

    if(conn->update(sql)){
        /*
            因为向数据库中插入新用户信息时没有指定主键id
            因为我们要获得自增的主键id，然后返回给客户端账号id
        */
        user.setId(mysql_insert_id(conn->getConnection())); 
        return true;
    }
    
    return false;
}


// 根据用户号码查询用户信息
User UserModel::query(int id)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from User where userid = %d", id);

    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();

    MYSQL_RES *res = conn->query(sql);
    if (res != nullptr)
    {
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row != nullptr)
        {
            User user;
            user.setId(atoi(row[0]));
            // 这里要注意，我们打算把一个char*类型传递给string&类型
            // 因为char*不是string，要隐式转换生成临时对象，因为形参必须是const的
            user.setName(row[1]);
            user.setPwd(row[2]);
            user.setState(row[3]);
            mysql_free_result(res);
            return user;
        }
    }
    return User();
}


bool UserModel::updateState(int userid, const string& state){
    char sql[1024] = {0};
    sprintf(sql, "update User set state = '%s' where userid = %d", state.c_str(), userid);
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    if(conn->update(sql)){
        return true;
    }
    return false;
}

// 重置用户的状态信息
bool UserModel::resetState(){
    char sql[1024] = "update User set state = 'offline' where state = 'online';";
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    shared_ptr<Connection> conn = cp->getConnection();
    conn->update(sql);
    return true;
}