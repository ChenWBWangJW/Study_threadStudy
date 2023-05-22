/****************************************
*要求：
*	通过移动构造函数来启动线程
*详解：
*	通过将对象t1转换为右值引用类型后进行调
*	用，从而实现移动语义，即将t1的资源所有
*	权转移给t2，从而实现通过移动构造函数来
*	启动线程
*****************************************/

#include<iostream>
#include<thread>

using namespace std;

void fun(int& n)		//引用传递，即直接引用该变量的地址从而直接修改值，无需在函数调用是创建隐式临时变量
{
	cout << "in fun:n=" << n << endl;
	n++;
	this_thread::sleep_for(chrono::milliseconds(10));		//this_thread 是 C++11 标准库中的一个命名空间，包含了与线程相关的函数和类型
}															//chrono是std命名空间下的一个子命名空间，用于定义时间相关的类，包括时间间隔、时间点、时钟等

int main(int argc, char const* argv[])
{
	int n = 0;

	cout << "n=" << n << endl;
	n = 10;

	thread t1(fun, ref(n));		//ref()函数用于将传入的参数转换为引用类型，即将n转换为引用类型
	thread t2(move(t1));		//move()函数用于将传入的参数转换为右值引用类型，即将t1转换为右值引用类型，右值引用类型的主要作用是实现移动语义，即将一个对象的资源所有权转移给另一个对象
	t2.join();					//右值引用类型的对象只能被移动，不能被复制，所以t1不能再被join()，只能用t2.join()
	
	cout << "n=" << n << endl;

	return 0;
}