#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int a = 200;
int b = 100;

void* threadA(void* x)
{
	while(1)
	{
		a -= 50;
		b += 50;
	}
}

void* threadB(void* x)
{
	while(1)
	{
		printf("%d\n", a + b);
		sleep(1);
	}
}

int main ()
{
	pthread_t tida, tidb;

	pthread_create(&tida, NULL, threadA, NULL);
	pthread_create(&tidb, NULL, threadB, NULL);
	pthread_join(tida, NULL);
	pthread_join(tidb, NULL);
	return 1;
}
