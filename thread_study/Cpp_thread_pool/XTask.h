#pragma once

class XTask
{
public:
	//一个人客户端一个base
	struct event_base* base = 0;
	int thread_id = 0;		//线程池ID

	//初始化任务
	virtual bool Init(int arg) = 0;
};