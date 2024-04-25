#ifndef CHAT_DATABASE_H//头文件防重
#define CHAT_DATABASE_H

#include <mysql/mysql.h>//mysql依赖，必须下载!
#include <iostream>//输入输出流
#include <stdio.h>//引入文件相关操作
#include <string.h>//c风格字符串

using namespace std;

class ChatDataBase
{
private:
	MYSQL *mysql;//创建Mysql对象
public:
	ChatDataBase();//管理聊天服务器的数据库操作
	~ChatDataBase();//释放

	void my_database_connect(const char *name);//初始化 ChatDataBase
	int my_database_get_group_name(string *);//初始化 ChatDataBase
	void my_database_get_group_member(string, string &);//用于连接到指定名称的数据库
	bool my_database_user_exist(string);//用于检查指定用户是否存在于数据库
	void my_database_user_password(string, string);//设置用户的密码
	bool my_database_password_correct(string, string);//检查用户输入的密码是否正确
	bool my_database_is_friend(string, string);//检查两个用户是否是是好友
	void my_database_get_friend_group(string, string &, string &);//获取好友信息
	void my_database_add_new_friend(string, string);//添加好友关系
	bool my_database_group_exist(string);//检查群组是否在数据库中
	void my_database_add_new_group(string, string);//添加群
	void my_database_user_add_group(string, string);//添加用户
	void my_database_group_add_user(string, string);//向群加用户
	void my_database_disconnect();//断开数据库的连接
};

#endif
