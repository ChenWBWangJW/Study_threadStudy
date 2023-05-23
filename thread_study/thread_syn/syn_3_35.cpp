/****************************************
*要求：
*	模拟卖货和查账线程观察调用情况
*详解：
*	通过互斥锁确保全局变量在被某个线程调用
*	时不会被其他线程打断
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<chrono>
#include<thread>

int a = 200;		//200元货物
int b = 100;		//100元现金

pthread_mutex_t* lock_ptr = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));		//定义互斥锁

void* ThreadA(void*)
{
	while (1)
	{
		pthread_mutex_lock(lock_ptr);
		a -= 50;		//卖出50元货物
		b += 50;		//得到50元现金
		pthread_mutex_unlock(lock_ptr);
	}
}

void* ThreadB(void*)		//模拟老板对账
{
	while (1)
	{
		pthread_mutex_lock(lock_ptr);
		printf("%d\n", a + b);		//打印总资产
		pthread_mutex_unlock(lock_ptr);
		std::this_thread::sleep_for(std::chrono::seconds(1));		//休眠1秒
	}
}

int main()
{
	pthread_t tid1, tid2;
	pthread_mutex_init(lock_ptr, NULL);				//初始化互斥锁
	pthread_create(&tid1, NULL, ThreadA, NULL);		//创建伙计卖货
	pthread_create(&tid2, NULL, ThreadB, NULL);		//创建老板对账
	pthread_join(tid1, NULL);						//等待线程结束
	pthread_join(tid2, NULL);						//等待线程结束
	pthread_mutex_destroy(lock_ptr);
	return 1;
}