/****************************************
*要求：
	创建一个不传参数的线程
*详解：
*	首先定义一个线程对象，定义对象后马上
*	启动线程，然后主线程休眠1秒，这样就
* 	保证了子线程能够执行完毕，然后主线程
* 	退出，子线程也会退出，预防主线程过早
* 	退出导致子线程没有机会执行
*****************************************/

#include<iostream>
#include<thread>
#include<unistd.h>

using namespace std;

void thfunc()
{
	cout << "thread start" << endl;
}

int main(int argc, char *argv[])
{
	thread t(thfunc);		//定义对象t并传入线程指针和线程函数参数
	sleep(1);

	return 0;
}