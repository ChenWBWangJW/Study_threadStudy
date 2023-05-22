/****************************************
*Ҫ��
*	�ѿ������߳�תΪ�����߳�(C++11&POSIX)
*��⣺
*	���ǵ���detach()�������̣߳��������߳�
*	�Ϳ��Բ��õȴ����߳̽����������Լ��Ƚ�
*	�������ǵ�����pthead_exit(NULL)������
* 	���̣߳��������߳̾ͻ�ȴ����߳̽�����
* 	�ٽ�����ֵ��һ���ʱ�������ȴ�ӡ���߳�
*	��k����������Ϊ�̻߳�û�����л���
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
	t.detach();		//���������߳�תΪ�����߳�

	cout << "in main:k=" << k << endl;
	pthread_exit(NULL);		//pthread_exit(NULL)��return 0;���������ڣ�ǰ�߻�ȴ������߳̽������ٽ������̣߳������򲻻�(���߳̽����������߳�Ҳ�����

	cout << "this line will not be printed" << endl;

	return 0;
}