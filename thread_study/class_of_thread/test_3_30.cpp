/****************************************
*要求：
*	暂停线程到下一分钟
*详解：
*	主线程从sleep_until处挂起，然后到了下
*	一个整分钟（分钟+1，秒钟为0，主线程继
*	续执行
*****************************************/

#include<iostream>		//std::cout
#include<thread>		//std::this_thread::sleep_unitl
#include<chrono>		//std::chrono:;system_clock
#include<ctime>			//std::time_t, std::tm, std::localtime, std::mktime
#include<time.h>
#include<stddef.h>

using namespace std;

void getNowTime()
{
	//timespec 是 C/C++ 中的一个结构体类型，用于表示时间的秒数和纳秒数。它通常用于高精度计时、时间戳等场景。
	timespec time;
	struct tm nowtime;
	clock_gettime(CLOCK_REALTIME, &time);		//引用相对于1970到现在的秒数

	localtime_r(&time.tv_sec, &nowtime);		//将秒数转换为时间结构体

	char current[1024];

	printf(
		"%04d-%02d-%02d %02d:%02d:%02d\n",
		nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday,
		nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec
	);
}

int main()
{
	//using 声明语句，用于在当前作用域中引入 std::chrono::system_clock 类型，使得我们可以直接使用 system_clock 类型而不需要每次都写完整的命名空间
	using std::chrono::system_clock;		

	//引入system_clock 类型
	//system_clock::now() 函数获取当前时间
	//system_clock::to_time_t() 函数将当前时间转换为 std::time_t 类型的时间值
	//结果保存在 tt 变量中
	//time_t 是 C/C++ 标准库中定义的一种数据类型，用于表示从 1970 年 1 月 1 日 00:00:00 UTC 开始经过的秒数，也称为 UNIX 时间戳。它通常用于表示绝对时间，可以用于计算时间间隔、时间比较等操作
	std::time_t tt = system_clock::to_time_t(system_clock::now());

	//使用 std::localtime() 函数将 std::time_t 类型的时间值转换为本地时间，并将结果保存在 struct std::tm* 类型的指针变量 ptm 中
	struct std::tm* ptm = std::localtime(&tt);		//将当前时间转换为时间结构体

	getNowTime();
	cout << "Waiting for the next minute to begin..." << endl;

	//ptm->tm_min 表示访问指针变量 ptm 所指向的 tm 结构体中的 tm_min 成员变量，并将其加 1
	//ptm->tm_sec 表示访问指针变量 ptm 所指向的 tm 结构体中的 tm_sec 成员变量，并将其赋值为 0
	//即修改结构体中的分钟+1，秒钟归零，意为在当前时间基础上加一分钟秒钟归零。如43.30变为44.00
	++ptm->tm_min;		//下一分钟
	ptm->tm_sec = 0;	//秒钟为0

	//mktime(ptm) 函数将 tm 结构体中的时间信息转换为 time_t 类型的时间值
	//system_clock::from_time_t() 函数将 time_t 类型的时间值转换为 system_clock::time_point 类型的时间点
	//this_thread::sleep_until() 函数则使当前线程休眠直到指定的时间点
	this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
	getNowTime();
	return 0;
}
