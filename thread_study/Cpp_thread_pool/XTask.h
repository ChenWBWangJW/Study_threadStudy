#pragma once

class XTask
{
public:
	//һ���˿ͻ���һ��base
	struct event_base* base = 0;
	int thread_id = 0;		//�̳߳�ID

	//��ʼ������
	virtual bool Init(int arg) = 0;
};