/****************************************
*Ҫ��
	���������߳�
*��⣺
*	����5���̶߳���ͨ������ʼ�����캯��
*	�ķ���ֵ��ֵ�����ǡ��÷����������̶߳�
*	�ǿ������̣߳����Ҫ�ú���join���ȴ���
*	�ǽ��������Է���ÿ�δ�ӡ˳�򲢲�һ����
*	��ΪCPU�̵߳��ȵ�����ԡ�
*****************************************/

#include<stdio.h>
#include<stdlib.h>

#include<chrono>	//std:chrono::seconnds
#include<thread>	//std::this_thread::sleep_for
#include<iostream>

using namespace std;

void thfunc(int n)		//�̺߳���
{
	std::cout << "thread: " << n << endl;
}

int main(int argc, const char* argv[])
{
	std::thread threads[5];
	std::cout << "create 5 threads...\n" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		threads[i] = std::thread(thfunc, i + 1);		//����ʼ�����캯������ֵ��ֵ���߳�
	}

	for (auto& t : threads)
	{
		t.join();
	}

	std::cout << "All threads joined.\n" << std::endl;

	return EXIT_SUCCESS;
}