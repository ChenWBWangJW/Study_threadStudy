/****************************************
*Ҫ��
*	����һ���̣߳������ݽṹ����Ϊ����
*��⣺
*	ͨ���ṹ�崫�ݶ��ֵ���̺߳���
*****************************************/

#include<iostream>
#include<thread>

using namespace std;

typedef struct
{
	int n;
	const char* str;		//�ṹ���еĳ�Ա����������string���ͣ���Ϊstring�������࣬���ǻ����������ͣ�����const���ͣ�������о���
} MyStruct;			//����ṹ������

void thfunc(void * arg)
{
	MyStruct* p = (MyStruct*)arg;		//ǿ��ת��void����ΪMyStruct����
	cout << "in thfunc:n=" << p->n << ",str=" << p->str << endl;
}

int main(int argc, char const* argv[])
{
	MyStruct mystruct;		//��ʼ���ṹ��
	mystruct.n = 100;
	mystruct.str = "hello world";

	thread t(thfunc, &mystruct);		//�����̶߳���t������ṹ�������ַ

	t.join();

	return 0;
}