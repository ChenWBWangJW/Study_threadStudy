#include "XThreadPool.h"
#include "XThread.h"
#include "mytask.h"

#define XThreadPoolGet XThreadPool::Get()

int main()
{
	int i;

	XThreadPoolGet->Init(10);//��ʼ���̳߳�
	CMyTask task[10];
	for (i = 0; i < 10; i++)
		XThreadPoolGet->Dispatch(&task[i], i);//��������
}