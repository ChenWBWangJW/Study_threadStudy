1.实现线程类
    定义一个类XThread，表示一个线程，里面包含成员函数实现了启动线程，
线程入口函数，线程激活，添加任务等功能，展示如下：

/************************************
* 类名：XThread
* 功能：线程类
* 属性：
* 		id - int类型，线程id
* 		base - event_base类型，libevent事件处理器，为方便管理线程，根据需要实现
* 		tasks - list<XTask*>类型，任务链表
* 		tasks_mutex - mutex类型，任务锁，在任务链表中添加和删除任务时需要用信号进行互斥
* 方法：
* 		Start() - 启动线程
* 		Main() - 线程入口函数
* 		Notify() - 通知线程
* 		Activate(int arg) - 激活线程
* 		AddTask(XTask *) - 添加任务
* 		XThread() - 构造函数
* 		~XThread() - 析构函数
* 说明：
*		线程类，用于管理线程
************************************/
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
	std::list<XTask*> tasks;				//任务链表
	std::mutex tasks_mutex;					//任务锁，在任务链表中添加和删除任务时需要用信号进行互斥
};


2.实现线程池类
    为管理线程，并以单例模式进行设计，保证线程安全性，主要提供两个函数接口，一个初始化所有线程，另一个分发任务
设计如下：

/************************************
* 类名：XThreadPool
* 功能：线程池类
* 属性：
* 	threadCount - int类型，线程数量
* 	lastThread - int类型，最后一个线程的id
* 	threads - vector<XThread *>类型，线程列表,用vector容器来管理线程
* 方法：
* 	Init(int threadCount) - 初始化所有线程
* 	Dispatch(XTask*, int arg) - 分发任务给线程
* 说明：
* 	线程池类，用于管理线程
* 	该类是单例模式
*************************************/
class XThreadPool{
public:
	/* 单例模式是一种创建型设计模式
	它保证一个类只有一个实例对象
	并提供一个全局访问点来访问这个实例对象
	单例模式通常用于管理全局资源
	例如日志、配置文件、数据库连接等 */
	static XThreadPool *Get()
	{
		static XThreadPool tp;
		return &tp;
	}
	void Init(int threadCount);		//初始化所有线程

	//分发任务给线程
	void Dispatch(XTask*, int arg);	//arg是任务所带的参数，可以自己重新实现，弄成更复杂的形式

private:
	int threadCount;			//线程数量
	int lastThread = -1;			//最后一个线程的id
	std::vector<XThread *> threads;	//线程列表,用vector容器来管理线程
	XThreadPool() {};
};


3.实现任务类
    有任务才能让线程池内的线程工作，这是一个描述任务的基类，设计如下：
    
/************************************
* 类名：XTask
* 功能：任务类
* 属性：
* 	base - event_base类型，libevent事件处理器，为方便管理线程，根据需要实现
* 	thread_id - int类型，线程id
* 方法：
*	Init(int arg) - 初始化任务
* 说明：
*	任务类，用于管理任务
*************************************/
class XTask
{
public:
	//一个客户端一个base
	struct event_base* base = 0;
	int thread_id = 0;		//线程池ID

	//初始化任务
	virtual bool Init(int arg) = 0;
};
