/****************************************
*Ҫ��
*	ģ�������Ͳ����̹߳۲�������
*��⣺
*	�����̱߳������̴߳�ϵ��½����������
*****************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int a = 200;		//200Ԫ����
int b = 100;		//100Ԫ�ֽ�

void* ThreadA(void*)
{
	while (1)
	{
		a -= 50;		//����50Ԫ����
		b += 50;		//�õ�50Ԫ�ֽ�
	}
}

void* ThreadB(void*)		//ģ���ϰ����
{
	while (1)
	{
		printf("%d\n", a + b);		//��ӡ���ʲ�
		sleep(1);
	}
}

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, ThreadA, NULL);		//�����������
	pthread_create(&tid2, NULL, ThreadB, NULL);		//�����ϰ����
	pthread_join(tid1, NULL);						//�ȴ��߳̽���
	pthread_join(tid2, NULL);						//�ȴ��߳̽���
	return 1;
}