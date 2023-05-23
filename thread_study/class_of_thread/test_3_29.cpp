/****************************************
*要求：
*	线程赛跑：创建10个线程，每个线程中让一
*	个变量从1累加到100万，谁先完成就打印谁
* 	的ID，以此排名。为公平起见，创建线程时
*	先不让他们1占用CPU时间，直到主线程改变
* 	标志位，所有线程同时开始工作。
*详解：
*	多次运行该程序，可发现每次结果都不相同
*	，线程启动时一直在while循环中通过yield
* 	让出CPU时间，直到主线程改变标志位，所有
*	线程同时开始工作，这样就能保证每个线程
*****************************************/

#include<iostream>		//std::cout
#include<thread>		//std::thread, std::this_thread::yield
#include<atomic>		//std::atomic_flag

using namespace std;

//atomic用来定义在全局变量ready上的操作都是原子操作，原子操作表示多个线程访问用一个全局资源时，能够确保所有其他线程都不在同一时间内访问相同资源
atomic<bool> ready(false);		//原子标志位，初始状态为false

void thfunc(int id)
{
	while (!ready)		//当标志位为false时，一直等待
	{
		this_thread::yield();		//让出CPU时间
	}

	//1.禁止编译器对变量的读写进行优化，以确保程序的正确性
	//2.防止编译器将变量的值缓存在寄存器中，而不是从内存中读取，从而导致其他线程无法看到该变量的更新
	//3.防止编译器改变变量的读写顺序，从而导致其他线程看到的顺序与实际不一致
	for (volatile int i = 0; i < 1000000; ++i)		//volatile防止编译器优化
	{}
	cout << id << ",";		//累加完毕，打印线程序号
}

int main()
{
	thread threads[10];		//创建10个线程，该对象存于数组中不具有特别的命名，通过数组下标指向某个线程，避免了拷贝构造函数而直接使用thread类构造函数提升效率
	cout << "Spawning 10 threads that count to 1 million..." << endl;
	for (int i = 0; i < 10; ++i)
	{
		threads[i] = thread(thfunc, i);
	}

	ready = true;

	for (auto& th : threads)
	{
		th.join();		//等待线程结束
	}

	cout << '\n';

	return 0;
}