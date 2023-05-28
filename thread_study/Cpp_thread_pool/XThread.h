#pragma once

#include<list>
#include<mutex>
class XTask;
struct event_base;
class XThread 
{
public:
	void Start();							//�����߳�
	void Main();							//�߳���ں���
	void Notify();
	void Activate(int arg);					//�����߳�
	void AddTask(XTask *);		//�������
	XThread();								//���캯��
	~XThread();								//��������
	int id = 0;								//�߳�id

private:
	event_base *base = 0;					//libevent�¼���������Ϊ��������̣߳�������Ҫʵ��
	std::list<XTask*> tasks;				//��������
	std::mutex tasks_mutex;					//����������������������Ӻ�ɾ������ʱ��Ҫ���źŽ��л���
};

