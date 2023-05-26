#include "thread_pool.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

/************************************
* ������CMyTask
* ���ܣ��̳���CTask�࣬ʵ��Run����
* ˵����
* 	1��Run�����У���ӡ�������ݣ��������1~4��
* 	2����������Ϊ����Ĳ���
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
	CMyTask taskObj;		//��������
	char szTmp[] = "hello, i m running!";		//��������
	taskObj.setData((void*)szTmp);		//������������
	CThreadPool threadpool(5);		//�����̳߳أ��̳߳����߳���Ϊ5

	for (int i = 0; i < 10; i++)
	{
		threadpool.AddTask(&taskObj);		//���̳߳����������
	}

	while (1)
	{
		printf("There are still %d tasks need to handle\n", threadpool.getTaskSize());

		//��������Ѿ�û������
		if (threadpool.getTaskSize() == 0)
		{
			//�����̳߳�
			//threadpool.StopAll() �������ȱ�ִ�У�Ȼ�󷵻�һ��ֵ��Ȼ���������ֵ�ᱻ�����ж�����
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
