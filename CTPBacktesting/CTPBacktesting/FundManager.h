//�ʽ�����࣬���˻���Ϣ���ºͼ�¼
//��ÿ�����Թ������ֲ֣������ʽ𣬶�̬Ȩ��
//��һ�棬�����Ȳ�ռ���ʽ�ֻ����ɽ�
#pragma once
#include "stdafx.h"
#include "TraderInfo.h"
#include "BacktestParam.h"

class FundManager {
public:
	FundManager();
	virtual ~FundManager();
private:
	double available_money;		//�����ʽ𣬳�ʼ��100W
	double floating_money;		//��̬Ȩ��
	map<string, int> net_pos;	//���ֲ�
};