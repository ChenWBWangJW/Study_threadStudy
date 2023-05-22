/****************************************
*要求：
	创建一个线程，并传递字符串作为参数
*详解：
*	无
*****************************************/

#include<iostream>
#include<thread>

using namespace std;

void thfunc(char* s)
{
	cout << "thfunc: " << s << endl;
}

int main(int argc, char* argv[])
{
	char s[] = "Hello World";		//定义一个字符串
	thread t(thfunc, s);		//定义线程对象，并传入字符串
	t.join();

	return 0;
}