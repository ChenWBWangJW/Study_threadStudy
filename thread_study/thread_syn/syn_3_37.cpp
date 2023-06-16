/****************************************
*要求：
*	找出1-20中能整除3的数
*详解：
*	thread1获取互斥锁mutex并判断i是否能被
*	3整除，如果能，则调用signal唤醒thread2
*	，thread2判定i能被三整除，则不进入if判
*	断语句执行printf函数，然后i++后再进行
*	判定，这次判定i不能被3整除，进入if，调
*	用wait等待thread1唤醒，不执行thread2后
*	的printf语句。thread1唤醒后，进行判断
* 	，i能被3整除，进入if，调用signal唤醒
*	thread2，以此循环。
* 附录：
*	//条件变量和互斥锁的初始化、销毁、加锁、解锁、条件变量的初始化、销毁、唤醒、等待
*	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
*	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
* 
*	//条件变量和互斥锁的释放
*	pthread_mutex_destroy(&mutex);
*	pthread_cond_destroy(&cond);
* 
*	//条件变量和互斥锁的加锁
*	pthread_cond_signal(&cond);
* 
*	//条件变量和互斥锁的解锁
*	pthread_cond_wait(&cond);
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread1(void*);
void* thread2(void*);

int i = 1;

int main(void)
{
	pthread_t t_a;
	pthread_t t_b;

	pthread_create(&t_a, NULL, thread1, (void*)NULL);
	pthread_create(&t_b, NULL, thread2, (void*)NULL);
	pthread_join(t_b, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	exit(0);
}

void* thread1(void* arg)
{
	for (i = 1; i <= 20; i++)
	{
		pthread_mutex_lock(&mutex);		//锁住互斥锁
		if (i % 3 == 0)
		{
			pthread_cond_signal(&cond);		//唤醒等待条件变量cond线程
		}
		else
		{
			printf("thread1:%d\n", i);		//打印不能整除3的i
		}
		pthread_mutex_unlock(&mutex);		//解锁互斥锁
		sleep(1);
	}
}

void* thread2(void* arg)
{
	while (i < 20)
	{
		pthread_mutex_lock(&mutex);
		if (i % 3 != 0)
		{
			/*调用时需要释放一个已经上锁的锁；
			收到信号返回时则需要对一个未上锁的互斥锁上锁*/
			pthread_cond_wait(&cond, &mutex);		//等待条件变量cond
		}
		printf("----------------thread2:%d\n", i);		//该代码被wait函数阻塞后不执行，直到thread1发送signal信号唤醒thread2后再直接执行该代码
		pthread_mutex_unlock(&mutex);
		sleep(1);
		i++;
	}
}
