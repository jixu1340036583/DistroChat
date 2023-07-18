#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

// 匹配User表的ORM类
class User{
public:
    User(int id = -1, string name = "", string pwd = "", string state = "offline"):\
    _id(id), _name(name), _password(pwd), _state(state){}
    void setId(int id){ _id = id;}
    void setName(const string& name){ _name = name; }
    void setPwd(const string& pwd){ _password = pwd; }
    void setState(const string state){ _state = state; }
    int getId() const { return _id; }
    string getName() const { return _name; }
    string getPwd() const { return _password; }
    string getState() const { return _state; }
    
private:
    int _id;
    string _name;
    string _password;
    string _state;
};

#endif