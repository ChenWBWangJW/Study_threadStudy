/****************************************
*Ҫ��
	����һ���̣߳��������ַ�����Ϊ����
*��⣺
*	��
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
	char s[] = "Hello World";		//����һ���ַ���
	thread t(thfunc, s);		//�����̶߳��󣬲������ַ���
	t.join();

	return 0;
}