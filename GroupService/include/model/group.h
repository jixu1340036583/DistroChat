#ifndef GROUP_H
#define GROUP_H

#include "groupuser.h"
#include <string>
#include <vector>
using namespace std;

// User表的ORM类
class Group
{
public:
    Group(string name = "", string desc = "", int id = -1): id(id), name(name), desc(desc){}

    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setDesc(string desc) { this->desc = desc; }

    int getId() { return this->id; }
    string getName() { return this->name; }
    string getDesc() { return this->desc; }
    vector<GroupUser> &getUsers() { return this->users; }

private:
    int id;
    string name;
    string desc;
    vector<GroupUser> users;
};

#endif