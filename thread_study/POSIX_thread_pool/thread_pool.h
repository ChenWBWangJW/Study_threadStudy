#ifndef _THREAD_POOL_H
#define	_THREAD_POOL_H

#include <vector>
#include <string>
#include <pthread.h>

using namespace std;

/************************************
* ������CTask
* ���ܣ�ִ���������
* ���ԣ�
*		m_strTaskName - string���ͣ����������
* 		m_ptrData - void*���ͣ�ָ��Ҫִ�е�����ľ�������
* ������
* 		CTask() - ���캯��
* 		CTask(string& taskName) - ���캯������
* 		Run() - �麯��������������̳������ʵ��
* 		setData(void* data) - �����������ݣ���ͨ������Ա
* 		~CTask() - ���������������ͷ���Դ
* ˵����ִ��������ࣺ�����������ݲ�ִ�У�����Ķ������̳߳ع���������Run����ִ������
************************************/
class CTask
{
protected:
	string m_strTaskName;		//���������
	void* m_ptrData;			//Ҫִ�е�����ľ�������

public:
	CTask() = default;		//���캯��
	CTask(string& taskName)		//���캯������
		: m_strTaskName(taskName)
		, m_ptrData(NULL)
	{};
	virtual int Run() = 0;		//�麯��������������̳������ʵ��,����������д�麯��ʱ����Ҫʹ�� override �ؼ��֣���ȷ������ǩ���ͻ����е��麯��һ��
	void setData(void* data);		//�����������ݣ���ͨ������Ա

	virtual ~CTask() {};		//���������������ͷ���Դ
};

/*�̳߳ع�����*/
/************************************
* ������CThreadPool
* ���ܣ��̳߳ع�����
* ���ԣ�
* 		m_vecTaskList - vector<CTask*>���ͣ������б�
* 		shutdown - bool���ͣ��߳��˳���־
* 		m_iThreadNum - int���ͣ��̳߳����������߳���
* 		pthread_id - pthread_t*���ͣ��߳�id����ָ��
* 		m_pthreadMutex - pthread_mutex_t���ͣ��߳�ͬ����
* 		m_pthreadCond - pthread_cond_t���ͣ��߳�ͬ����������
* ������
* 		ThreadFunc(void* threadDate) - ���̵߳��̻߳ص�����
* 		MoveToIdle(pthread_t tid) - �߳�ִ�н����󣬰��Լ���������߳���
* 		MoveToBusy(pthread_t tid) - ���뵽æµ�߳���ȥ
* 		Create() - �����̳߳��е��߳�
* 		AddTask(CTask* task) - ��������ӵ����������
* 		StopAll() - ʹ�̳߳��е��߳��˳�
* 		getTaskSize() - ��ȡ��ǰ��������е�������
* 		getBusySize() - ��ȡ��ǰæ���߳�����δʵ��
* 		getAliveSize() - ��ȡ��ǰ�����߳�����δʵ��
* 		getWaitSize() - ��ȡ��ǰ�ȴ����߳�����δʵ��
* 		Destroy() - �ȴ��߳��˳�������̳߳أ�δʵ��
* ˵�����̳߳ع����ࣺ�����̳߳أ�������������̳߳ص�
************************************/
class CThreadPool
{
private:
	static vector<CTask*> m_vecTaskList;		//�����б�
	static bool shutdown;						//�߳��˳���־
	int m_iThreadNum;							//�̳߳����������߳���
	pthread_t* pthread_id;						//�߳�id����ָ��
	static pthread_mutex_t m_pthreadMutex;		//�߳�ͬ����
	static pthread_cond_t m_pthreadCond;		//�߳�ͬ����������

protected:
	static void* ThreadFunc(void* threadDate);		//���̵߳��̻߳ص�����
	static int MoveToIdle(pthread_t tid);			//�߳�ִ�н����󣬰��Լ���������߳���
	static int MoveToBusy(pthread_t tid);			//���뵽æµ�߳���ȥ
	int Create();									//�����̳߳��е��߳�

public:
	CThreadPool(int threadNum);						//���캯��
	int AddTask(CTask* task);						//��������ӵ����������
	int StopAll();									//ʹ�̳߳��е������߳��˳�
	int getTaskSize();								//��ȡ��ǰ��������е�������
};

#endif // !_THREAD_POOL_H

