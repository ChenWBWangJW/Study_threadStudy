#include <thread>
#include <iostream>
using namespace std;
#include <unistd.h>
#include "testUtil.h"
#include "XThread.h"
#include "XTask.h"

//�����̣߳�����һ��ִ��������Ϊ���ܻ�û��������
void XThread::Start()
{
	testout(id << "thread At Start()");
	thread th(&XThread::Main, this);		//�߳�һ�����������Ϳ�ʼִ�У�
	th.detach();						//�̷߳��룬����Ҫ�ȴ��߳̽�����ͬ����̶߳�������
}

//�߳�����ʱ��������
void XThread::Main()
{
	cout << id << "thread At Main() begin" << endl;
	cout << id << "thread At Main() end" << endl;
}

void XThread::Activate(int arg)
{
	testout(id << "thread At Activate");

	//�������б��л�ȡ���񲢳�ʼ��
	XTask *t = NULL;
	tasks_mutex.lock();
	if (tasks.empty())
	{
		tasks_mutex.unlock();
		return;
	}
	t = tasks.front();
	tasks.pop_front();		//��������
	tasks_mutex.unlock();
	t->Init(arg);			//��ʼ������
}

//�������
void XThread::AddTask(XTask* t)
{
	if (!t) return;
	t->base = this->base;
	tasks_mutex.lock();		//�������ҲҪ����
	tasks.push_back(t);		//�������
	tasks_mutex.unlock();	//����
}
XThread::XThread()
{
}

XThread::~XThread()
{
}