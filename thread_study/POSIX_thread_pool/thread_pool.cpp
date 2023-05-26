#include "thread_pool.h"
#include <cstdio>

/************************************
* ��������setData
* �����ࣺCTask
* ���ܣ�����CTask�������ֵ
* ���룺
*	data - void*���ͣ�ָ��Ҫ���õ�����ֵ
* ����ֵ��
*	��
*************************************/
void CTask::setData(void* data)
{
	m_ptrData = data;
}

//��̬��ʼ����Ա
vector<CTask*> CThreadPool::m_vecTaskList;		//һ���洢CTask���͵�ָ�������������ָ��TaskList�ڵ�Ԫ�أ�������������
bool CThreadPool::shutdown = false;
pthread_mutex_t CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t CThreadPool::m_pthreadCond = PTHREAD_COND_INITIALIZER;


/************************************
* ��������CThreadPool
* �����ࣺCThreadPool
* ���ܣ����캯������ʼ���̳߳�
* ���룺
* 	threadNum - int���ͣ��̳߳����������߳���
* ����ֵ��
* 	��
* ˵����
* 	����һ�������������ø������������̳߳ص�
*	��������������Ӧ�������̵߳Ĵ���
*************************************/
CThreadPool::CThreadPool(int threadNum)
{
	this->m_iThreadNum = threadNum;
	printf("I will create %d threads.\n", threadNum);
	Create();
}


/************************************
* ��������ThreadFunc
* �����ࣺCThreadPool
* ���ܣ����̵߳��̻߳ص�����
* ���룺
* 	threadData - void*���ͣ�ָ���߳�����
* ����ֵ��
* 	��
* ˵����
* 	1����ȡ����pid
		2����ȡͬ����
		3���������Ϊ�գ������̣߳��ȴ������������У����Զ��ͷ�ͬ����
		4������̳߳��˳���־Ϊfalse������ͣ״̬�����ͷ�ͬ��������ӡ�߳�״̬
		5������������û��ɣ����ȡ�����б��еĵ�һ��Ԫ�أ��������������еĵ�һ������
		6���ж��Ƿ�Ϊֻ��һ�����񣬼�����ָ����ָ���ַ�Ƿ�һ��
		7�����������������б����Լ���ȡ��������
		8���ͷ�ͬ����
		9��ִ������
*************************************/
void* CThreadPool::ThreadFunc(void* threadData)
{
	pthread_t tid = pthread_self();
	while (1)
	{
		pthread_mutex_lock(&m_pthreadMutex);

		//�������Ϊ�գ��ȴ�������������
		while (m_vecTaskList.size() == 0 && !shutdown)
		{
			pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);
		}

		//�ر��߳�
		if (shutdown)
		{
			pthread_mutex_unlock(&m_pthreadMutex);
			printf("[tid: %lu]\texit\n", pthread_self());
			pthread_exit(NULL);
		}

		printf("[tid: %lu]\trun: ", tid);
		/*vector<CTask*>::iterator ��ʾһ��ָ�� CTask* ����Ԫ�ص����������, ���ڱ��������е�Ԫ��
		  ��δ���������Ƕ���һ��ָ�� m_vecTaskList �е�һ��Ԫ�صĵ������������������� m_vecTaskList �е�����Ԫ��*/
		vector<CTask*>::iterator iter = m_vecTaskList.begin();		

		//ȡ��һ�����񲢴���֮
		CTask* task = *iter;
		if (iter != m_vecTaskList.end())		//�����б����Ƿ�ֻ��һ�������ж�Ϊ�񣬽����������
		{
			task = *iter;		//*iter ��ʾ������ iter ��ָ���Ԫ�ر�����iterָ����һ���������������Ǹõ������е�Ԫ��
			//�� m_vecTaskList ��ɾ�������� iter ��ָ���Ԫ�أ�������ָ��ɾ��Ԫ��֮���Ԫ�صĵ�����
			m_vecTaskList.erase(iter);		//ɾ�������б����ѱ�ȡ��������
		}

		pthread_mutex_unlock(&m_pthreadMutex);
		task->Run();		//ִ������
		printf("[tid: %lu]\tidle\n", tid);
	}

	return (void*)0;
}


/*************************************
* ��������AddTask
* �����ࣺCThreadPool
* ���ܣ��������
* ���룺
* 	task - CTask*���ͣ�ָ��Ҫ��ӵ�����
* ����ֵ��
* 	0 - �ɹ�
* 	-1 - ʧ��
* ˵����
* 	1����ȡͬ����
* 	2����������ӵ������б���
* 	3���ͷ�ͬ����
* 	4�������߳�ͬ���ź�
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
* ��������Create
* �����ࣺCThreadPool
* ���ܣ������߳�
* ���룺
* 	��
* ����ֵ��
* 	0 - �ɹ�
* 	-1 - ʧ��
* ˵����
* 	1��ʹ�� new ������ڶ��Ϸ���һ�� pthread_t ���͵Ķ�̬����
* 	2������ĳ���Ϊ m_iThreadNum������������׵�ַ��ֵ��ָ����� pthread_id
* 	3������ m_iThreadNum ���߳�
* 	4������ 0
* 	5����������߳�ʧ�ܣ��򷵻� -1(δʵ��
* 	6������̳߳��Ѿ��������򷵻� -1��δʵ��
* 	7������̳߳ش����ɹ����򷵻� 0
/*************************************/
int CThreadPool::Create()
{
	/*��δ����������ʹ�� new ������ڶ��Ϸ���һ�� pthread_t ���͵Ķ�̬����
	  ����ĳ���Ϊ m_iThreadNum������������׵�ַ��ֵ��ָ����� pthread_id*/
	pthread_id = new pthread_t[m_iThreadNum];
	for (int i = 0; i < m_iThreadNum; i++)
	{
		pthread_create(&pthread_id[i], NULL, ThreadFunc, NULL);
	}

	return 0;
}


/*************************************
* ��������StopAll
* �����ࣺCThreadPool
* ���ܣ�ֹͣ�����߳�
* ���룺
* 	��
* ����ֵ��
* 	0 - �ɹ�
* 	-1 - ʧ��
* ˵����
* 	1���ж��̳߳��˳���־����Ϊtrue������
	2����Ϊfalse���趨Ϊtrue�����������������㲥�źţ����������߳�
	3����������߳�
	4���ͷ� pthread_id ָ��Ķ�̬������ռ�õ��ڴ棬����ָ�� pthread_id ��Ϊ NULL
	5������ͬ��������������
*************************************/
int CThreadPool::StopAll()
{
	//�����ظ�����
	if (shutdown)
	{
		return -1;
	}

	printf("Now I will end all threads!\n\n");

	//�������еȴ��̣߳��̳߳�Ҫ������
	shutdown = true;
	pthread_cond_broadcast(&m_pthreadCond);

	//������ʬ�߳�
	for (int i = 0; i < m_iThreadNum; i++)
	{
		pthread_join(pthread_id[i], NULL);
	}

	delete[] pthread_id;
	pthread_id = NULL;

	//���ٻ���������������
	pthread_mutex_destroy(&m_pthreadMutex);
	pthread_cond_destroy(&m_pthreadCond);

	return 0;
}


/*************************************
* ��������getTaskSize
* �����ࣺCThreadPool
* ���ܣ���ȡ��ǰ������������
* ���룺
* 	��
* ����ֵ��
* 	��ǰ������������
*************************************/
int CThreadPool::getTaskSize()
{
	return m_vecTaskList.size();
}