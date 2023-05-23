/****************************************
*要求：
*	不同线程同步的多线程累加
*详解：
*	结果并不是每个线程都完成了累加
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/timeb.h>
#include<string.h>
#include<cstdlib>

int gcn = 0;

void* thread_1(void* arg)
{
	int j = 0;
	for (j = 0; j < 10000; j++)
	{
		gcn++;
	}
	pthread_exit((void *)0);
}

void* thread_2(void* arg)
{
	int j = 0;
	for (j = 0; j < 10000; j++)
	{
		gcn++;
	}
	pthread_exit((void*)0);
}

int main(void)
{
	int j, err;
	pthread_t tid1, tid2;

	for (j = 0; j < 10; j++)
	{
		err = pthread_create(&tid1, NULL, thread_1, (void*)0);
		if (err != 0)
		{
			printf("create new thread failed\n");
			exit(0);
		}

		err = pthread_create(&tid2, NULL, thread_2, (void*)0);
		if (err != 0)
		{
			printf("create new thread failed\n");
			exit(0);
		}

		err = pthread_join(tid1, NULL);
		if (err != 0)
		{
			printf("wait thread done error:%s\n", strerror(err));
		}

		err = pthread_join(tid2, NULL);
		if (err != 0)
		{
			printf("wait thread done error:%s\n", strerror(err));
		}

		printf("gcn = %d\n", gcn);
		gcn = 0;
	}

	return 0;
}