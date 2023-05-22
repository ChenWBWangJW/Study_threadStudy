/****************************************
*要求：
*	创建一个线程，并传递结构体作为参数
*详解：
*	通过结构体传递多个值给线程函数
*****************************************/

#include<iostream>
#include<thread>

using namespace std;

typedef struct
{
	int n;
	const char* str;		//结构体中的成员变量不能是string类型，因为string类型是类，不是基本数据类型，需标记const类型，否则会有警告
} MyStruct;			//定义结构体类型

void thfunc(void * arg)
{
	MyStruct* p = (MyStruct*)arg;		//强制转换void类型为MyStruct类型
	cout << "in thfunc:n=" << p->n << ",str=" << p->str << endl;
}

int main(int argc, char const* argv[])
{
	MyStruct mystruct;		//初始化结构体
	mystruct.n = 100;
	mystruct.str = "hello world";

	thread t(thfunc, &mystruct);		//定义线程对象t并传入结构体变量地址

	t.join();

	return 0;
}