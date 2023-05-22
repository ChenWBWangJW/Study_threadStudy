#ifndef _GUN_SOURCE
#define _GUN_SOURCE		//getattr_t函数需要，定义在pthread.h前
#endif
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void * pthread_attributes(void *arg)
{
	int i, s;
	pthread_attr_t gattr;	//定义线程属性结构体

	s = pthread_getattr_np(pthread_self(), &gattr);		//获取当前线程属性结构体,使用该函数需在pthread.h前定义宏_GUN_SOURCE
	if(s != 0)
	{
		printf("pthread_getattr_np failed\n");		//打印错误信息
	}

	s = pthread_attr_getdetachstate(&gattr, &i);		//从属性结构值中获取分离状态属性
	if(s)
	{
		printf("pthread_attr_getdatachstate failed\n");
	}

	printf("Detach state = %s\n",		//打印当前分离状态属性
		(i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
		(i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
		"???");

	pthread_detach(pthread_self());

	s = pthread_getattr_np(pthread_self(), &gattr);
	if(s != 0)
	{
		printf("pthread_getattr_np failed\n");		//打印错误信息
	}

	s = pthread_attr_getdetachstate(&gattr, &i);		//从属性结构值中获取分离状态属性
	if(s)
	{
		printf("pthread_attr_getdatachstate failed\n");
	}

	printf("After pthread_detach\nDetach state = %s\n",		//打印当前分离状态属性
		(i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
		(i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
		"UNKNOW_ATTRIBUTE");

	pthread_attr_destroy(&gattr);		//所设置结构体不再被需要则需要销毁
}

int main(int argc, char * arg [ ])
{
	pthread_t pthread_id;
	int s;

	s = pthread_create(&pthread_id, NULL, &pthread_attributes, NULL);		//创建线程
	if(s != 0)
	{
			printf("pthread_cteate failed");
			return 0;
	}

	pthread_exit(NULL);		//等待子线程结束
}

