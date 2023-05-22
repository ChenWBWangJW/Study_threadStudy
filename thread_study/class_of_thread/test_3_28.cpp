/****************************************
*要求：
*	线程比较
*详解：
*	is_main_thread第一次调用是作为主线程
*	中的普通函数，得到的ID也与main函数的
*	主线程ID相同，第二次是子线程，则得到
*	的是子线程ID。this_thread是一个命名空间
*	，用来表示当前线程，get_id()是获取当前
*	线程的ID。
*****************************************/

#include<iostream>		//std::cout
#include<thread>		//std::thread, std::this_thread::ID, std::this_thread::get_id

using namespace std;

thread::id main_thread_id = this_thread::get_id();		//获取主线程ID，该函数作用域在

void is_main_thread()
{
	if(main_thread_id == this_thread::get_id())		//判断是否和主线程ID相同
		cout << "This is main thread, main thread ID:" << main_thread_id << endl;
	else
		cout << "This is not main thread."<< endl;
}

int main()
{
	is_main_thread();		//作为主函数的普通函数进行调用
	thread th(is_main_thread);		//作为线程函数进行调用
	th.join();

	return 0;
}