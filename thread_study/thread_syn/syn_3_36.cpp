/****************************************
*Ҫ��
*	��д���������ٶȱȽ�
*��⣺
*	���н��
*	total mutex time:1729 ms
*	total rwlock time:2835 ms
*	���Կ�����д�������Ʋ������ٶ��ϣ�����
*	���ڶ�д���Ķ������Ա�����߳�ͬʱ����
*	����������ֻ�ܱ�һ���̳߳��У������Ϳ���
*	��߳���Ĳ����ԡ�
* ��¼��
*	��ȡ����ʱ��ķ���
* 
*	#include<sys/time.h>
*	......
*	struct timeval start;
*	clock_t t1, t2;
*	struct timeval end;
* 	gettimeofday(&start, NULL);
*	{
*		������ʱ������......
*	}
*	gettimeofday(&end, NULL);
*	long long total_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
*	total_time /= 1000;
*	printf("total time:%lld ms\n", total_time);
*	......
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include<string.h>
#include<cstdlib>

int gnc = 0;

pthread_mutex_t* mutex_ptr = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
pthread_rwlock_t* rwlock_ptr = (pthread_rwlock_t*)malloc(sizeof(pthread_rwlock_t));

void* ThreadA(void*)
{
	int j;
	volatile int a;
	for (j = 0; j < 10000000; j++)
	{
		pthread_mutex_lock(mutex_ptr);
		a = gnc;
		pthread_mutex_unlock(mutex_ptr);
	}
	pthread_exit((void*)0);
}

void* ThreadB(void*)
{
	int j;
	volatile int b;
	for (j = 0; j < 10000000; j++)
	{
		pthread_mutex_lock(mutex_ptr);
		b = gnc;
		pthread_mutex_unlock(mutex_ptr);
	}
	pthread_exit((void*)0);
}

void* ThreadC(void*)
{
	int j;
	volatile int a;
	for (j = 0; j < 10000000; j++)
	{
		pthread_rwlock_rdlock(rwlock_ptr);
		a = gnc;
		pthread_rwlock_unlock(rwlock_ptr);
	}
	pthread_exit((void*)0);
}

void* ThreadD(void*)
{
	int j;
	volatile int b;
	for (j = 0; j < 10000000; j++)
	{
		pthread_rwlock_rdlock(rwlock_ptr);
		b = gnc;
		pthread_rwlock_unlock(rwlock_ptr);
	}
	pthread_exit((void*)0);
}

int mutexVar(void)
{
	int j, err;
	pthread_t th1, th2;

	struct timeval start;
	clock_t t1, t2;
	struct timeval end;
	
	pthread_mutex_init(mutex_ptr, NULL);
	
	gettimeofday(&start, NULL);

	err = pthread_create(&th1, NULL, ThreadA, (void*)0);
	if (err != 0)
	{
		printf("create new thread error:%s\n", strerror(err));
	}
	err = pthread_create(&th2, NULL, ThreadB, (void*)0);
	if (err != 0)
	{
		printf("create new thread error:%s\n", strerror(err));
	}
	err = pthread_join(th1, NULL);
	if (err != 0)
	{
		printf("wait thread done error:%s\n", strerror(err));
	}
	err = pthread_join(th2, NULL);
	if (err != 0)
	{
		printf("wait thread done error:%s\n", strerror(err));
	}

	gettimeofday(&end, NULL);

	pthread_mutex_destroy(mutex_ptr);

	long long total_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

	total_time /= 1000;
	printf("total mutex time:%lld ms\n", total_time);

	return 0;
}

int rdlockVer(void)
{
	int j, err;
	pthread_t th1, th2;

	struct timeval start;
	clock_t t1, t2;
	struct timeval end;

	pthread_rwlock_init(rwlock_ptr, NULL);

	gettimeofday(&start, NULL);

	err = pthread_create(&th1, NULL, ThreadC, (void*)0);
	if (err != 0)
	{
		printf("create new thread error:%s\n", strerror(err));
	}
	err = pthread_create(&th2, NULL, ThreadD, (void*)0);
	if (err != 0)
	{
		printf("create new thread error:%s\n", strerror(err));
	}
	err = pthread_join(th1, NULL);
	if (err != 0)
	{
		printf("wait thread done error:%s\n", strerror(err));
	}
	err = pthread_join(th2, NULL);
	if (err != 0)
	{
		printf("wait thread done error:%s\n", strerror(err));
	}

	gettimeofday(&end, NULL);

	pthread_rwlock_destroy(rwlock_ptr);

	long long total_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

	total_time /= 1000;
	printf("total rwlock time:%lld ms\n", total_time);

	return 0;
}

int main()
{
	mutexVar();
	rdlockVer();

	return 0;
}