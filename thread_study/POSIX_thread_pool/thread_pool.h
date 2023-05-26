#ifndef _THREAD_POOL_H
#define	_THREAD_POOL_H

#include <vector>
#include <string>
#include <pthread.h>

using namespace std;

/************************************
* 类名：CTask
* 功能：执行任务的类
* 属性：
*		m_strTaskName - string类型，任务的名称
* 		m_ptrData - void*类型，指向要执行的任务的具体数据
* 方法：
* 		CTask() - 构造函数
* 		CTask(string& taskName) - 构造函数重载
* 		Run() - 虚函数，供基类子类继承类具体实现
* 		setData(void* data) - 设置任务数据，普通函数成员
* 		~CTask() - 析构函数，用于释放资源
* 说明：执行任务的类：设置任务数据并执行，该类的对象由线程池管理，调用其Run方法执行任务
************************************/
class CTask
{
protected:
	string m_strTaskName;		//任务的名称
	void* m_ptrData;			//要执行的任务的具体数据

public:
	CTask() = default;		//构造函数
	CTask(string& taskName)		//构造函数重载
		: m_strTaskName(taskName)
		, m_ptrData(NULL)
	{};
	virtual int Run() = 0;		//虚函数，供基类子类继承类具体实现,派生类中重写虚函数时，需要使用 override 关键字，以确保函数签名和基类中的虚函数一致
	void setData(void* data);		//设置任务数据，普通函数成员

	virtual ~CTask() {};		//析构函数，用于释放资源
};

/*线程池管理类*/
/************************************
* 类名：CThreadPool
* 功能：线程池管理类
* 属性：
* 		m_vecTaskList - vector<CTask*>类型，任务列表
* 		shutdown - bool类型，线程退出标志
* 		m_iThreadNum - int类型，线程池中启动的线程数
* 		pthread_id - pthread_t*类型，线程id数组指针
* 		m_pthreadMutex - pthread_mutex_t类型，线程同步锁
* 		m_pthreadCond - pthread_cond_t类型，线程同步条件变量
* 方法：
* 		ThreadFunc(void* threadDate) - 新线程的线程回调函数
* 		MoveToIdle(pthread_t tid) - 线程执行结束后，把自己放入空闲线程中
* 		MoveToBusy(pthread_t tid) - 移入到忙碌线程中去
* 		Create() - 创建线程池中的线程
* 		AddTask(CTask* task) - 把任务添加到任务队列中
* 		StopAll() - 使线程池中的线程退出
* 		getTaskSize() - 获取当前任务队列中的任务数
* 		getBusySize() - 获取当前忙的线程数（未实现
* 		getAliveSize() - 获取当前存活的线程数（未实现
* 		getWaitSize() - 获取当前等待的线程数（未实现
* 		Destroy() - 等待线程退出，清除线程池（未实现
* 说明：线程池管理类：创建线程池，添加任务，销毁线程池等
************************************/
class CThreadPool
{
private:
	static vector<CTask*> m_vecTaskList;		//任务列表
	static bool shutdown;						//线程退出标志
	int m_iThreadNum;							//线程池中启动的线程数
	pthread_t* pthread_id;						//线程id数组指针
	static pthread_mutex_t m_pthreadMutex;		//线程同步锁
	static pthread_cond_t m_pthreadCond;		//线程同步条件变量

protected:
	static void* ThreadFunc(void* threadDate);		//新线程的线程回调函数
	static int MoveToIdle(pthread_t tid);			//线程执行结束后，把自己放入空闲线程中
	static int MoveToBusy(pthread_t tid);			//移入到忙碌线程中去
	int Create();									//创建线程池中的线程

public:
	CThreadPool(int threadNum);						//构造函数
	int AddTask(CTask* task);						//把任务添加到任务队列中
	int StopAll();									//使线程池中的所有线程退出
	int getTaskSize();								//获取当前任务队列中的任务数
};

#endif // !_THREAD_POOL_H

