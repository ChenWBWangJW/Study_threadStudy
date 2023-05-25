/****************************************
*Ҫ��
*	�������汾��д��3_38
*��⣺
*	��
*****************************************/

#include<iostream>
#include<mutex>
#include<thread>

volatile int counter(0);		//volatile��ֹ�������Ż�������һ��ȫ�ֱ���
std::mutex mtx;

void thrfunc()
{
	if (mtx.try_lock())
	{
		++counter;
		mtx.unlock();
	}
	else
	{
	std::cout << "try_lock failed" << std::endl;
	}
}

int main(int argc, const char* argv[])
{
	std::thread threads[10];
	for (int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(thrfunc);		//����10���߳�
	}

	for (auto& th : threads)
	{
		th.join();		//�ȴ��߳̽���
	}

	std::cout << "count to " << counter << " successfully" << std::endl;

	return 0;
}