#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thfunc(void *arg)
{
	printf("sub thread is running!\n");
	return NULL;
}

int main(int argc, char *arg[])
{
	pthread_t thread_id;
	pthread_attr_t thread_attr;
	struct sched_param thread_param;
	size_t stack_size;
	int res;

	res = pthread_attr_init(&thread_attr);		//初始化线程状态
	if(res)
	{
			printf("pthread_attr_init failed:");
	}

	res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);	//设置分离模式
	if(res)
	{
			printf("pthread_attr_detachstate failed:");
	}

	res = pthread_create(&thread_id, &thread_attr, thfunc, NULL);
	if(res)
	{
			printf("pthread_createt failed:");
	}
	printf("main thread will exit\n");

	pthread_exit(NULL);
	orintf("main thread has exited, this line will not run\n");
	
	return 0;
}
