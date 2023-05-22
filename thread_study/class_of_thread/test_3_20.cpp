/****************************************
*要求：
	批量创建线程
*详解：
*	定义5个线程对象，通过将初始化构造函数
*	的返回值赋值给他们。该方法所创建线程都
*	是可连接线程，因此要用函数join来等待他
*	们结束，可以发现每次打印顺序并不一致是
*	因为CPU线程调度的随机性。
*****************************************/

#include<stdio.h>
#include<stdlib.h>

#include<chrono>	//std:chrono::seconnds
#include<thread>	//std::this_thread::sleep_for
#include<iostream>

using namespace std;

void thfunc(int n)		//线程函数
{
	std::cout << "thread: " << n << endl;
}

int main(int argc, const char* argv[])
{
	std::thread threads[5];
	std::cout << "create 5 threads...\n" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		threads[i] = std::thread(thfunc, i + 1);		//将初始化构造函数返回值赋值于线程
	}

	for (auto& t : threads)
	{
		t.join();
	}

	std::cout << "All threads joined.\n" << std::endl;

	return EXIT_SUCCESS;
}