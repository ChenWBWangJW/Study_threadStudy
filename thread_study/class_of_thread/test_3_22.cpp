/****************************************
*要求：
	创建一个线程并传入整型参数
*详解：
*	创建线程时，把一个整型作为参数传给构造
*	函数，然后在线程函数中打印出来，并且使
*	用join()等待线程结束，函数join会一直等
*	到子线程结束才返回并执行该函数后面的代
*	码
*****************************************/

#include<iostream>
#include<thread>

using namespace std;

void thfunc(int n)		//线程函数
{
	cout << "thfunc: " << n << endl;		//n为1
}

int main(int argc, char* argv[])
{
	thread t1(thfunc, 1);		//定义线程对象t1，并传入线程函数指针和线程函数参数
	t1.join();		//等待线程对象t1结束
	return 0;
}