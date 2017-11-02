//��������ݿ��ж�ȡ����
#pragma once
#include "stdafx.h"
#include "mysql.h"
#include "MyStrategy.h"
#include <fstream>
#include <iostream>
using namespace std;

class DBReader {
public:
	DBReader();									//����ʵ������ȡ���ĵĺ�Լ
	void Register(MyStrategy *strategy);		//ע�����ʵ��
	void PlayMarketData();						//�������飬�����첽���ƣ��ȶ�ȡ��ϣ�Ȼ��ز�
	virtual ~DBReader();						//������Դ
private:
	MYSQL *my_db;								//���ݿ��ȡָ��
	MyStrategy *my_strategy;					//����ʵ�����˴����Խ�����չ
	map<string, vector<FT_DATA>> market_data;	//������Ϣ
	vector<string> instrument_array;			//���ĵ�����
	
	//���ݿ�������Ϣ
	string user;
	string pswd;
	string host;
	string database;
	string table;
};