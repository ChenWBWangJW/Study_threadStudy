/****************************************
*要求：
*	用互斥锁的多线程累加
*详解：
*	通过互斥锁限制全局变量修改的过程，以
*	保护修改过程不会被打断
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include<string.h>
#include<cstdlib>

int gnc = 0;

pthread_mutex_t *pmutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

void* thread_1(void* arg) 
{
	int i = 0;
	for (i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(pmutex);
		gnc++;
		pthread_mutex_unlock(pmutex);
	}
	pthread_exit((void*)0);
}

void* thread_2(void* arg)
{
	int j;
	for (j = 0; j < 1000000; j++)
	{
		pthread_mutex_lock(pmutex);
		gnc++;
		pthread_mutex_unlock(pmutex);
	}
	pthread_exit((void*)0);
}

int main() 
{
	int j, err;
	pthread_t tid1, tid2;
	int count = 0;

	pthread_mutex_init(pmutex, NULL);
	for (int i = 0; i < 10; i++)
	{
		err = pthread_create(&tid1, NULL, thread_1, (void*)0);
		if (err != 0)
		{
			printf("create new thread failed:%s\n", strerror(err));
			exit(0);
		}
		else
		{
			count++;
		}

		err = pthread_create(&tid2, NULL, thread_2, (void*)0);
		if (err != 0)
		{
			printf("create new thread failed:%s\n", strerror(err));
			exit(0);
		}
		else
		{
			count++;
		}

		err = pthread_join(tid1, NULL);
		if (err != 0)
		{
			printf("wait thread failed:%s\n", strerror(err));
			exit(1);
		}

		err = pthread_join(tid2, NULL);
		if (err != 0)
		{
			printf("wait thread failed:%s\n", strerror(err));
			exit(1);
		}
		printf("gcn=%d\n", gnc);
		gnc = 0;

	}
	printf("count = %d\n", count);
	pthread_mutex_destroy(pmutex);
	return 0;
}