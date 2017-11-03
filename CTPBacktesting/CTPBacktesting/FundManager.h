//�ʽ�����࣬���˻���Ϣ���ºͼ�¼
//��ÿ�����Թ������ֲ֣������ʽ𣬶�̬Ȩ��
//��һ�棬�����Ȳ�ռ���ʽ�ֻ����ɽ�
#pragma once
#include "stdafx.h"
#include "TraderInfo.h"
#include "BacktestParam.h"

extern map<string, vector<int>> net_pos;

class FundManager {
public:
	FundManager();
	virtual ~FundManager();
	void InTradeEquity(MyTrade *trade);															//�ɽ��У������˻���Ϣ
	void InMarketEquity(map<string, vector<FT_DATA>> &market_data, string InstrumentID);		//�����мۼ���Ȩ��
private:
	double available_money;					//�����ʽ𣬳�ʼ��100W
	double floating_interest;				//��̬Ȩ��
	vector<pair<double, double>> equity;	//ȫʱ�����еĶ�̬Ȩ�棬������ʾЧ��
};