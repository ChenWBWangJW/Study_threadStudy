/****************************************
*Ҫ��
*	ģ�������Ͳ����̹߳۲�������
*��⣺
*	ͨ��������ȷ��ȫ�ֱ����ڱ�ĳ���̵߳���
*	ʱ���ᱻ�����̴߳��
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<chrono>
#include<thread>

int a = 200;		//200Ԫ����
int b = 100;		//100Ԫ�ֽ�

pthread_mutex_t* lock_ptr = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));		//���廥����

void* ThreadA(void*)
{
	while (1)
	{
		pthread_mutex_lock(lock_ptr);
		a -= 50;		//����50Ԫ����
		b += 50;		//�õ�50Ԫ�ֽ�
		pthread_mutex_unlock(lock_ptr);
	}
}

void* ThreadB(void*)		//ģ���ϰ����
{
	while (1)
	{
		pthread_mutex_lock(lock_ptr);
		printf("%d\n", a + b);		//��ӡ���ʲ�
		pthread_mutex_unlock(lock_ptr);
		std::this_thread::sleep_for(std::chrono::seconds(1));		//����1��
	}
}

int main()
{
	pthread_t tid1, tid2;
	pthread_mutex_init(lock_ptr, NULL);				//��ʼ��������
	pthread_create(&tid1, NULL, ThreadA, NULL);		//�����������
	pthread_create(&tid2, NULL, ThreadB, NULL);		//�����ϰ����
	pthread_join(tid1, NULL);						//�ȴ��߳̽���
	pthread_join(tid2, NULL);						//�ȴ��߳̽���
	pthread_mutex_destroy(lock_ptr);
	return 1;
}