/****************************************
*Ҫ��
*	����һ���̣߳�������������̺߳���
*��⣺
*	���������������캯����ͬʱ�̺߳���Ҳ
*	Ҫ׼����ͬ������βΣ�ͨ�������ε�ַ&k
*	�����ã����߳����޸�������ָ��ı�����
*	���ݣ����������߳���k��ֵҲ���޸���
*****************************************/

#include<iostream>
#include<thread>

using namespace std;

void thfunc(int n, int m, int *pk, char s[])
{
	cout << "in thfunc:n=" <<  n << ",m=" << m << ",*pk=" << *pk << ",s=" << s << endl;
	*pk = 100;		//*pkΪֱ��ָ���ָ����ָ������pk��Ϊ��ַ���ô���Ϊֱ���޸�ָ�����
}

int main(int argc, char const* argv[])
{
	int n = 100, m = 200, k = 5;
	char str[] = "hello world";
	thread t(thfunc, n, m, &k, str);

	t.join();
	cout << "in main:k=" << k << endl;

	return 0;
}