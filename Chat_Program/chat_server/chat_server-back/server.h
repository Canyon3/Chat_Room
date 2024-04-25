//Author:canyon 2024/4/1
#ifndef SERVER_H
#define SERVER_H

#include <event.h> //包含event头文件
#include <string.h>//String类
#include <sys/socket.h> //包含了套接字（socket）相关的函数和数据结构
#include <netinet/in.h> //定义了地址的下常量定义
#include <arpa/inet.h> //处理ip地址
#include <thread> //线程相关函数
#include <iostream> //输出输出流
#include <event2/listener.h> //用于创建和管理网络监听器的函数
#include "chatlist.h" //包含chatlist.h相关函数与成员
#include <jsoncpp/json/json.h> //封装JSON对象相关函数
#include <unistd.h> //操作系统交互和系统调用

using namespace std;

#define IP     "10.23.87.4" //服务器ip，我设置为虚拟机的ip(一直未能解决连通云服务器，所以需要登陆就修改。--ifconfig查看)
#define PORT   8000 //后端端口号
#define MAXSIZE  1024 * 1024 //缓冲区最大尺寸

class Server
{
private:
	struct event_base *base;          //事件集合
	struct evconnlistener *listener;    //监听事件
	static ChatInfo *chatlist;                //链表对象（含有两个链表）
	static ChatDataBase *chatdb;              //数据库对象   

private:
	static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int socklen, void *arg);//处理新连接
	static void client_handler(int); //处理用户操作
	static void send_file_handler(int, int, int *, int *);//处理发送文件请求
	static void read_cb(struct bufferevent *bev, void *ctx);//处理读取事件回调
	static void event_cb(struct bufferevent *bev, short what, void *ctx);//处理读取事件回调

	static void server_register(struct bufferevent *bev, Json::Value val);//处理客户端注册
	static void server_login(struct bufferevent *bev, Json::Value val);//处理客户端注册
	static void server_add_friend(struct bufferevent *bev, Json::Value val);//添加好友
	static void server_create_group(struct bufferevent *bev, Json::Value val);//创建群
	static void server_add_group(struct bufferevent *bev, Json::Value val);//加群
	static void server_private_chat(struct bufferevent *bev, Json::Value val);//私聊
	static void server_group_chat(struct bufferevent *bev, Json::Value val);//群聊
	static void server_get_group_member(struct bufferevent *bev, Json::Value val);//获取群成员列表
	static void server_user_offline(struct bufferevent *bev, Json::Value val);//下线通知
	static void server_send_file(struct bufferevent *bev, Json::Value val);//客户端发文件

public:
	Server(const char *ip = "127.0.0.1", int port = 8000);//创建Server对象，包括ip和端口号
	~Server(); //释放
};

#endif
