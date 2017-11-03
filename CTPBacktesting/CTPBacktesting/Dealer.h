//���ϵͳ���Լ۳ɽ������ع���
//��һ��˳��ϵͳ�����漰�첽����߳�
#pragma once
#include "stdafx.h"
#include "TraderInfo.h"
#include "MyStrategy.h"
#include <iostream>
using namespace std;

class Dealer {
public:
	Dealer(vector<string> &instrument_array);													
	virtual ~Dealer();
	void Register(MyStrategy *strategy);												//ע�����ʵ��
	void OrderAction();																	//α�챨��
	void Strike(map<string, vector<FT_DATA>> &market_data, string InstrumentID);		//�����̿���Ϣ�гɽ�����һ�������ع��ƣ��������
private:	
	MyStrategy *my_strategy;					//���ά������ʵ������OnRtn�ӿ�
	map<string, map<int, ORDER>> ctp_order;		//α��Ľ��������У��ú�Լ�б�ͱ��������˫������
	thread LittleDealer;						//����ת���߳�
	MyTrade *my_trade;							//α��ĳɽ���
};