/****************************************
*Ҫ��
*	�ҳ�1-20��������3����
*��⣺
*	thread1��ȡ������mutex���ж�i�Ƿ��ܱ�
*	3����������ܣ������signal����thread2
*	��thread2�ж�i�ܱ����������򲻽���if��
*	�����ִ��printf������Ȼ��i++���ٽ���
*	�ж�������ж�i���ܱ�3����������if����
*	��wait�ȴ�thread1���ѣ���ִ��thread2��
*	��printf��䡣thread1���Ѻ󣬽����ж�
* 	��i�ܱ�3����������if������signal����
*	thread2���Դ�ѭ����
* ��¼��
*	//���������ͻ������ĳ�ʼ�������١����������������������ĳ�ʼ�������١����ѡ��ȴ�
*	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
*	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
* 
*	//���������ͻ��������ͷ�
*	pthread_mutex_destroy(&mutex);
*	pthread_cond_destroy(&cond);
* 
*	//���������ͻ������ļ���
*	pthread_cond_signal(&cond);
* 
*	//���������ͻ������Ľ���
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
		pthread_mutex_lock(&mutex);		//��ס������
		if (i % 3 == 0)
		{
			pthread_cond_signal(&cond);		//���ѵȴ���������cond�߳�
		}
		else
		{
			printf("thread1:%d\n", i);		//��ӡ��������3��i
		}
		pthread_mutex_unlock(&mutex);		//����������
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
			pthread_cond_wait(&cond, &mutex);		//�ȴ���������cond
		}
		printf("----------------thread2:%d\n", i);		//�ô��뱻wait����������ִ�У�ֱ��thread1����signal�źŻ���thread2����ֱ��ִ�иô���
		pthread_mutex_unlock(&mutex);
		sleep(1);
		i++;
	}
}