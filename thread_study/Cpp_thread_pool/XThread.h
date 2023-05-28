#pragma once

#include<list>
#include<mutex>
class XTask;
struct event_base;
class XThread 
{
public:
	void Start();							//启动线程
	void Main();							//线程入口函数
	void Notify();
	void Activate(int arg);					//激活线程
	void AddTask(XTask *);		//添加任务
	XThread();								//构造函数
	~XThread();								//析构函数
	int id = 0;								//线程id

private:
	event_base *base = 0;					//libevent事件处理器，为方便管理线程，根据需要实现
	std::list<XTask*> tasks;				//任务联保
	std::mutex tasks_mutex;					//任务锁，在任务链表中添加和删除任务时需要用信号进行互斥
};

