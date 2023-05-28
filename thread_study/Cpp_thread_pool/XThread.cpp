#include <thread>
#include <iostream>
using namespace std;
#include <unistd.h>
#include "testUtil.h"
#include "XThread.h"
#include "XTask.h"

//启动线程，但不一定执行任务，因为可能还没出现任务
void XThread::Start()
{
	testout(id << "thread At Start()");
	thread th(&XThread::Main, this);		//线程一旦被创建，就开始执行；
	th.detach();						//线程分离，不需要等待线程结束，同意该线程独立运行
}

//线程启动时做的事情
void XThread::Main()
{
	cout << id << "thread At Main() begin" << endl;
	cout << id << "thread At Main() end" << endl;
}

void XThread::Activate(int arg)
{
	testout(id << "thread At Activate");

	//从任务列表中获取任务并初始化
	XTask *t = NULL;
	tasks_mutex.lock();
	if (tasks.empty())
	{
		tasks_mutex.unlock();
		return;
	}
	t = tasks.front();
	tasks.pop_front();		//弹出任务
	tasks_mutex.unlock();
	t->Init(arg);			//初始化任务
}

//添加任务
void XThread::AddTask(XTask* t)
{
	if (!t) return;
	t->base = this->base;
	tasks_mutex.lock();		//添加任务也要上锁
	tasks.push_back(t);		//添加任务
	tasks_mutex.unlock();	//解锁
}
XThread::XThread()
{
}

XThread::~XThread()
{
}