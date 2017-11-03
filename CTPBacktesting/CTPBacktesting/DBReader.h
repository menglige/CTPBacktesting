//��������ݿ��ж�ȡ����
#pragma once
#include "stdafx.h"
#include "mysql.h"
#include "MyStrategy.h"
#include "Dealer.h"
#include "FundManager.h"
#include <fstream>
#include <iostream>
using namespace std;

class DBReader {
public:
	DBReader();																	//����ʵ������ȡ���ĵĺ�Լ
	void Register(MyStrategy *strategy, Dealer *dealer, FundManager *fm);		//ע�����ʵ��
	void PlayMarketData();														//�������飬�����첽���ƣ��ȶ�ȡ��ϣ�Ȼ��ز�
	vector<string> RtnInstrumentArray() {										//��¶���ĵĺ�Լ�б�
		return instrument_array;
	}
	virtual ~DBReader();										//������Դ
private:
	MYSQL *my_db;								//���ݿ��ȡָ��
	MyStrategy *my_strategy;					//����ʵ�����˴����Խ�����չ
	Dealer *my_dealer;							//���ʵ��
	FundManager *my_fm;							//�ʽ����ʵ��
	map<string, vector<FT_DATA>> market_data;	//������Ϣ
	vector<string> instrument_array;			//���ĵ�����
	
	//���ݿ�������Ϣ
	string user;
	string pswd;
	string host;
	string database;
	string table;
};