/****************************************
*Ҫ��
*	�̱߳Ƚ�
*��⣺
*	is_main_thread��һ�ε�������Ϊ���߳�
*	�е���ͨ�������õ���IDҲ��main������
*	���߳�ID��ͬ���ڶ��������̣߳���õ�
*	�������߳�ID��this_thread��һ�������ռ�
*	��������ʾ��ǰ�̣߳�get_id()�ǻ�ȡ��ǰ
*	�̵߳�ID��
*****************************************/

#include<iostream>		//std::cout
#include<thread>		//std::thread, std::this_thread::ID, std::this_thread::get_id

using namespace std;

thread::id main_thread_id = this_thread::get_id();		//��ȡ���߳�ID���ú�����������

void is_main_thread()
{
	if(main_thread_id == this_thread::get_id())		//�ж��Ƿ�����߳�ID��ͬ
		cout << "This is main thread, main thread ID:" << main_thread_id << endl;
	else
		cout << "This is not main thread."<< endl;
}

int main()
{
	is_main_thread();		//��Ϊ����������ͨ�������е���
	thread th(is_main_thread);		//��Ϊ�̺߳������е���
	th.join();

	return 0;
}