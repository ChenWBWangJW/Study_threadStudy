/****************************************
*要求：
*	模拟卖货和查账线程观察调用情况
*详解：
*	卖货线程被查账线程打断导致结果出现问题
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int a = 200;		//200元货物
int b = 100;		//100元现金

void* ThreadA(void*)
{
	while (1)
	{
		a -= 50;		//卖出50元货物
		b += 50;		//得到50元现金
	}
}

void* ThreadB(void*)		//模拟老板对账
{
	while (1)
	{
		printf("%d\n", a + b);		//打印总资产
		sleep(1);
	}
}

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, ThreadA, NULL);		//创建伙计卖货
	pthread_create(&tid2, NULL, ThreadB, NULL);		//创建老板对账
	pthread_join(tid1, NULL);						//等待线程结束
	pthread_join(tid2, NULL);						//等待线程结束
	return 1;
}