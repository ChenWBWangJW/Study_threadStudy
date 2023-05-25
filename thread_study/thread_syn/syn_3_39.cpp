/****************************************
*要求：
*	非阻塞版本改写例3_38
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
		threads[i] = std::thread(thrfunc);		//创建10个线程
	}

	for (auto& th : threads)
	{
		th.join();		//等待线程结束
	}

	std::cout << "count to " << counter << " successfully" << std::endl;

	return 0;
}