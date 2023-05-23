/****************************************
*Ҫ��
*	��ͣ�̵߳���һ����
*��⣺
*	
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
	timespec time;
	struct tm nowtime;
	clock_gettime(CLOCK_REALTIME, &time);		//���������1970�����ڵ�����

	localtime_r(&time.tv_sec, &nowtime);		//������ת��Ϊʱ��ṹ��
	char current[1024];
	printf(
		"%04d-%02d-%02d %02d:%02d:%02d\n",
		nowtime.tm_year + 1900, nowtime.tm_mon + 1, nowtime.tm_mday,
		nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec
	);
}

int main()
{
	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());
	struct std::tm* ptm = std::localtime(&tt);
	getNowTime();
	cout << "Waiting for the next minute to begin..." << endl;
	++ptm->tm_min;
	ptm->tm_sec = 0;
	this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));		//��ִͣ�е���һ��������
	getNowTime();
	return 0;
}