#ifndef _GUN_SOURCE
#define _GUN_SOURCE
#endif
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handle_errno_en(en, msg)		//输出自定义错误信息
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void * thread_start(void *arg)
{
	int i, s;
	pthread_attr_t gattr;	//定义线程属性结构体

	s = pthread_getattr_np(pthread_self(), &gattr);		//获取当前线程属性结构体
	if(s != 0)
	{
		handle_errno_en(s, "pthread_getattr_np");		//打印错误信息
	}

	printf("thread's detachstat attributes:\n");

	s = pthread_attr_getdetachstate(&gattr, &i);		//从属性结构值中获取分离状态属性
	if(s)
	{
		handle_errno_en(s, "pthread_attr_getdatachstate");
	}

	printf("Detach state    = %s\n",		//打印当前分离状态属性
		(i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
		(i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
		"???");

	//pthread_attr_destory(&gattr);
}

int main(int argc, char * arg [ ])
{
	pthread_t thr;
	int s;

	s = pthread_create(&thr, NULL, &thread_start, NULL);		//创建线程
	if(s != 0)
	{
			handle_errno_en(s, "pthread_cteate");
			return 0;
	}

	pthread_join(thr, NULL);		//等待子线程结束
	
	return 0;
}

