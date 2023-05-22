/****************************************
*要求：
*	创建一个线程，传多个参数给线程函数
*详解：
*	传入多个参数给构造函数，同时线程函数也
*	要准备好同样多的形参，通过对整形地址&k
*	的引用，在线程中修改了他所指向的变量的
*	内容，所以在主线程中k的值也被修改了
*****************************************/

#include<iostream>
#include<thread>

using namespace std;

void thfunc(int n, int m, int *pk, char s[])
{
	cout << "in thfunc:n=" <<  n << ",m=" << m << ",*pk=" << *pk << ",s=" << s << endl;
	*pk = 100;		//*pk为直接指向该指针所指变量，pk则为地址，该代码为直接修改指向变量
}

int main(int argc, char const* argv[])
{
	int n = 100, m = 200, k = 5;
	char str[] = "hello world";
	thread t(thfunc, n, m, &k, str);

	t.join();
	cout << "in main:k=" << k << endl;

	return 0;
}