#include "thread_pool.h"
#include <cstdio>

/************************************
* 函数名：setData
* 所属类：CTask
* 功能：设置CTask类的属性值
* 输入：
*	data - void*类型，指向要设置的属性值
* 返回值：
*	无
*************************************/
void CTask::setData(void* data)
{
	m_ptrData = data;
}

//静态初始化成员
vector<CTask*> CThreadPool::m_vecTaskList;		//一个存储CTask类型的指针的容器，用于指向TaskList内的元素，即待处理任务
bool CThreadPool::shutdown = false;
pthread_mutex_t CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t CThreadPool::m_pthreadCond = PTHREAD_COND_INITIALIZER;


/************************************
* 函数名：CThreadPool
* 所属类：CThreadPool
* 功能：构造函数，初始化线程池
* 输入：
* 	threadNum - int类型，线程池中启动的线程数
* 返回值：
* 	无
* 说明：
* 	传递一个参数，并设置该类内启动的线程池的
*	数量，并进行相应数量的线程的创建
*************************************/
CThreadPool::CThreadPool(int threadNum)
{
	this->m_iThreadNum = threadNum;
	printf("I will create %d threads.\n", threadNum);
	Create();
}


/************************************
* 函数名：ThreadFunc
* 所属类：CThreadPool
* 功能：新线程的线程回调函数
* 输入：
* 	threadData - void*类型，指向线程数据
* 返回值：
* 	无
* 说明：
* 	1）获取自身pid
		2）获取同步锁
		3）如果队列为空，阻塞线程，等待新任务加入队列，并自动释放同步锁
		4）如果线程池退出标志为false，即关停状态，则释放同步锁，打印线程状态
		5）以上条件都没达成，则获取任务列表中的第一个元素，即待处理任务中的第一个任务
		6）判断是否为只有一个任务，即两个指针所指向地址是否一致
		7）擦除待处理任务列表中以及提取出的任务
		8）释放同步锁
		9）执行任务
*************************************/
void* CThreadPool::ThreadFunc(void* threadData)
{
	pthread_t tid = pthread_self();
	while (1)
	{
		pthread_mutex_lock(&m_pthreadMutex);

		//如果队列为空，等待新任务进入队列
		while (m_vecTaskList.size() == 0 && !shutdown)
		{
			pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);
		}

		//关闭线程
		if (shutdown)
		{
			pthread_mutex_unlock(&m_pthreadMutex);
			printf("[tid: %lu]\texit\n", pthread_self());
			pthread_exit(NULL);
		}

		printf("[tid: %lu]\trun: ", tid);
		/*vector<CTask*>::iterator 表示一个指向 CTask* 类型元素的正向迭代器, 用于遍历容器中的元素
		  这段代码的作用是定义一个指向 m_vecTaskList 中第一个元素的迭代器，可以用来遍历 m_vecTaskList 中的所有元素*/
		vector<CTask*>::iterator iter = m_vecTaskList.begin();		

		//取出一个任务并处理之
		CTask* task = *iter;
		if (iter != m_vecTaskList.end())		//任务列表中是否只有一个任务，判定为否，进入条件语句
		{
			task = *iter;		//*iter 表示迭代器 iter 所指向的元素本身，而iter指的是一个迭代器，而不是该迭代器中的元素
			//从 m_vecTaskList 中删除迭代器 iter 所指向的元素，并返回指向被删除元素之后的元素的迭代器
			m_vecTaskList.erase(iter);		//删除任务列表中已被取出的任务，
		}

		pthread_mutex_unlock(&m_pthreadMutex);
		task->Run();		//执行任务
		printf("[tid: %lu]\tidle\n", tid);
	}

	return (void*)0;
}


/*************************************
* 函数名：AddTask
* 所属类：CThreadPool
* 功能：添加任务
* 输入：
* 	task - CTask*类型，指向要添加的任务
* 返回值：
* 	0 - 成功
* 	-1 - 失败
* 说明：
* 	1）获取同步锁
* 	2）将任务添加到任务列表中
* 	3）释放同步锁
* 	4）发出线程同步信号
***************************************/
int CThreadPool::AddTask(CTask* task)
{
	pthread_mutex_lock(&m_pthreadMutex);
	m_vecTaskList.push_back(task);
	pthread_mutex_unlock(&m_pthreadMutex);
	pthread_cond_signal(&m_pthreadCond);

	return 0;
}


/*************************************
* 函数名：Create
* 所属类：CThreadPool
* 功能：创建线程
* 输入：
* 	无
* 返回值：
* 	0 - 成功
* 	-1 - 失败
* 说明：
* 	1）使用 new 运算符在堆上分配一个 pthread_t 类型的动态数组
* 	2）数组的长度为 m_iThreadNum，并将数组的首地址赋值给指针变量 pthread_id
* 	3）创建 m_iThreadNum 个线程
* 	4）返回 0
* 	5）如果创建线程失败，则返回 -1(未实现
* 	6）如果线程池已经创建，则返回 -1（未实现
* 	7）如果线程池创建成功，则返回 0
/*************************************/
int CThreadPool::Create()
{
	/*这段代码的作用是使用 new 运算符在堆上分配一个 pthread_t 类型的动态数组
	  数组的长度为 m_iThreadNum，并将数组的首地址赋值给指针变量 pthread_id*/
	pthread_id = new pthread_t[m_iThreadNum];
	for (int i = 0; i < m_iThreadNum; i++)
	{
		pthread_create(&pthread_id[i], NULL, ThreadFunc, NULL);
	}

	return 0;
}


/*************************************
* 函数名：StopAll
* 所属类：CThreadPool
* 功能：停止所有线程
* 输入：
* 	无
* 返回值：
* 	0 - 成功
* 	-1 - 失败
* 说明：
* 	1）判断线程池退出标志，若为true，返回
	2）若为false，设定为true，并发送条件变量广播信号，阻塞所有线程
	3）清除所有线程
	4）释放 pthread_id 指向的动态数组所占用的内存，并将指针 pthread_id 置为 NULL
	5）销毁同步锁和条件变量
*************************************/
int CThreadPool::StopAll()
{
	//避免重复调用
	if (shutdown)
	{
		return -1;
	}

	printf("Now I will end all threads!\n\n");

	//唤醒所有等待线程，线程池要销毁了
	shutdown = true;
	pthread_cond_broadcast(&m_pthreadCond);

	//消除僵尸线程
	for (int i = 0; i < m_iThreadNum; i++)
	{
		pthread_join(pthread_id[i], NULL);
	}

	delete[] pthread_id;
	pthread_id = NULL;

	//销毁互斥量和条件变量
	pthread_mutex_destroy(&m_pthreadMutex);
	pthread_cond_destroy(&m_pthreadCond);

	return 0;
}


/*************************************
* 函数名：getTaskSize
* 所属类：CThreadPool
* 功能：获取当前队列中任务数
* 输入：
* 	无
* 返回值：
* 	当前队列中任务数
*************************************/
int CThreadPool::getTaskSize()
{
	return m_vecTaskList.size();
}