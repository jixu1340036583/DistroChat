#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <iostream>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <memory>
#include <functional>

#include "Connection.h"

class ConnectionPool
{
public:
	// 单例接口
	static ConnectionPool* getConnectionPool();
	// 给外部提供的接口，从连接池中获取一个空闲连接
	shared_ptr<Connection> getConnection();
private:
	// 构造函数私有化
	ConnectionPool();
	~ConnectionPool();

	// 从配置文件中加载配置项
	void Trim(std::string& src_buf); // 去掉字符串前后的空格
	bool loadConfigFile(); 

	// 运行在独立的线程中，专门负责生产新连接
	void produceConnectionTask();

	// 扫描超过maxIdleTime时间的空闲连接，进行对于的连接回收
	void scannerConnectionTask();

	std::string ip_; // mysql的ip地址
	unsigned short port_; // mysql的端口号 3306
	std::string username_; // mysql登录用户名
	std::string password_; // mysql登录密码
	std::string dbname_; // 连接的数据库名称
	int initSize_; // 连接池的初始连接量
	int maxSize_; // 连接池的最大连接量
	int maxIdleTime_; // 连接池最大空闲时间
	int connectionTimeout_; // 连接池获取连接的超时时间

	std::unordered_map<std::string, std::string> m_configMap; // 配置文件
	std::queue<Connection*> connectionQue_; // 存储mysql连接的队列
	std::mutex queueMutex_; // 维护连接队列的线程安全互斥锁
	std::atomic_int connectionCnt_; // 记录连接所创建的connection连接的总数量 
	std::condition_variable cv_not_empty; 
	std::condition_variable cv_is_empty;
	bool running_ = false;
};	