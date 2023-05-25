/****************************************
*要求：
*	多线程统计计数器到10万
*详解：
*	无
*****************************************/

#include<iostream>
#include<mutex>
#include<thread>

volatile int counter(0);		//volatile防止编译器优化，设置一个全局变量
std::mutex mtx;

void thrfunc()
{
	for (int i = 0; i < 10000; i++)
	{
		mtx.lock();
		++counter;
		mtx.unlock();
	}
}

int main(int argc, const char* argv[])
{
	std::thread threads[10];
	for (int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(thrfunc);		//创建10个线程
	}

	for (auto& th : threads)
	{
		th.join();		//等待线程结束
	}

	std::cout << "count to" << counter << "successfully" << std::endl;

	return 0;
}