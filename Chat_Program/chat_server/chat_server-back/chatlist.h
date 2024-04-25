#ifndef CHATINFO_H //防止头文件重复！
#define CHATINFO_H

#include <event.h>//事件处理
#include <list>//链表
#include "chat_database.h"//引入聊天数据库

using namespace std;

#define MAXNUM    1024     //表示群最大个数

struct User//用户展示信息
{
	string name; //用户名
	struct bufferevent *bev;//通信指针
};
typedef struct User User;//简化

struct GroupUser//表示群组中的用户信息，只包含用户名 name
{
	string name;
};
typedef struct GroupUser GroupUser;//简化

struct Group//表示群组中的用户信息，只包含用户名 name
{
	string name;
	list<GroupUser> *l;
};
typedef struct Group Group;//简化

class Server;

class ChatInfo//聊天信息
{
	friend class Server;//Server可访问ChatInfo
private:
	list<User> *online_user;     //保存所有在线的用户信息
	list<Group> *group_info;     //保存所有群信息
	ChatDataBase *mydatabase;    //数据库对象

public:
	ChatInfo();
	~ChatInfo();

	bool info_group_exist(string);//判断指定名称的群组是否存在
	bool info_user_in_group(string, string);//判断指定名称的群组是否存在
	void info_group_add_user(string, string);//用于向指定群组中添加用户
	struct bufferevent *info_get_friend_bev(string);//用于获取指定用户对应的对象指针
	string info_get_group_member(string);//用于获取指定群组的成员列表
	void info_add_new_group(string, string);//加群消息
};

#endif
