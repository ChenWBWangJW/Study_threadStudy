/****************************************
*要求：
*	暂停线程5秒
*详解：
*	无
*****************************************/

#include<iostream>
#include<thread>
#include<chrono>

int main()
{
	std::cout << "countdown:\n";
	for (int i = 5; i > 0; --i)
	{
		std::cout << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::cout << "Lift off!\n";

	return 0;
}