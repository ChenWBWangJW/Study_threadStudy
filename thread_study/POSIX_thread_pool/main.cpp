#include "thread_pool.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

/************************************
* 类名：CMyTask
* 功能：继承自CTask类，实现Run函数
* 说明：
* 	1）Run函数中，打印任务内容，随机休眠1~4秒
* 	2）任务内容为传入的参数
*
************************************/
class CMyTask : public CTask
{
public:
	CMyTask() = default;
	int Run()
	{
		printf("%s\n", (char*)m_ptrData);
		int x = rand() % 4 + 1;
		sleep(x);
		return 0;
	}
	~CMyTask(){}
};

int main()
{
	CMyTask taskObj;		//声明对象
	char szTmp[] = "hello, i m running!";		//设置数据
	taskObj.setData((void*)szTmp);		//设置任务数据
	CThreadPool threadpool(5);		//创建线程池，线程池中线程数为5

	for (int i = 0; i < 10; i++)
	{
		threadpool.AddTask(&taskObj);		//向线程池中添加任务
	}

	while (1)
	{
		printf("There are still %d tasks need to handle\n", threadpool.getTaskSize());

		//任务队列已经没有任务
		if (threadpool.getTaskSize() == 0)
		{
			//消除线程池
			//threadpool.StopAll() 函数会先被执行，然后返回一个值，然后这个返回值会被用于判断条件
			if (threadpool.StopAll() == -1)
			{
				printf("Thread pool clear, exit.\n");
				exit(0);
			}
		}
		sleep(2);
		printf("2 seconds later...\n");
	}
	return 0;
}
