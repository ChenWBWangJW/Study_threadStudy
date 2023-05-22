/****************************************
*要求：
*	把可连接线程转为分离线程(C++11&POSIX)
*详解：
*	我们调用detach()来分离线程，这样主线程
*	就可以不用等待子线程结束而可以自己先结
*	束。我们调用了pthead_exit(NULL)来结束
* 	主线程，这样主线程就会等待子线程结束后
* 	再结束。值得一提的时，他会先打印主线程
*	的k变量，是因为线程还没进行切换。
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
	t.detach();		//将可连接线程转为分离线程

	cout << "in main:k=" << k << endl;
	pthread_exit(NULL);		//pthread_exit(NULL)与return 0;的区别在于，前者会等待其他线程结束后再结束主线程，后者则不会(主线程结束后，其他线程也会结束

	cout << "this line will not be printed" << endl;

	return 0;
}