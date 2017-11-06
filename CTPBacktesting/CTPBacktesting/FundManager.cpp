#include "stdafx.h"
#include "FundManager.h"

FundManager::FundManager() {
	//��ʼ���ʽ�
	available_money = 1000000;
	
	//��ʼ�����ֲ�
	ifstream instrumentFile(BACKTEST_INSTRUMENT);
	if (instrumentFile.is_open()) {
		string len;
		getline(instrumentFile, len);
		int instrumentNum = stoi(len);
		for (int line = 0; line < instrumentNum; line++) {
			string instrument;
			getline(instrumentFile, instrument);
			net_pos.insert(make_pair(instrument, vector<int>()));
			cout << "Current instrument is: " << instrument << endl;
		}
	}
	else
		cout << "Cannot read instruments!" << endl;
	instrumentFile.close();
	
	//��ʼ�����ײ���
	ifstream feeFile(TRADE_PARAM_FILE);
	string param;
	while (getline(feeFile, param)) {
		string tmp = "";
		int field_index = 0;
		string InstrumentID;
		fee new_fee;
		for (int i = 0; i < param.size(); i++) {
			if (param[i] == ',') {
				switch (field_index) {
				case 0:
					cout << "InstrumentID is: " << tmp << endl;
					InstrumentID = tmp;
					break;
				case 1:
					cout << "Multiplier is: " << atof(tmp.c_str()) << endl;
					new_fee.multiplier = atof(tmp.c_str());
					break;
				case 2:
					cout << "Commission is: " << atof(tmp.c_str()) << endl;
					new_fee.commission = atof(tmp.c_str());
					break;
				}
				field_index++;
				tmp = "";
			}
			else
				tmp += param[i];
		}
		cout << "Deposit is: " << atof(tmp.c_str()) << endl;
		new_fee.deposit_percent = atof(tmp.c_str());
		trade_param.insert(make_pair(InstrumentID, new_fee));
	}
	feeFile.close();

	//��ʼ���˻�Ȩ��
	money_unit init_equity;
	init_equity.available_money = 1000000;
	init_equity.total_interest = 1000000;
	equity.push_back(init_equity);
	available_money = 1000000;
}

FundManager::~FundManager() {

}

//����ɽ��е��˻�Ȩ��
//���շֱʳɽ�ԭ�Ӽ���
void FundManager::InTradeEquity(MyTrade *trade, int cur_pos) {
	if (trade->Direction == '0') {
		if (cur_pos > 0) 	//�࿪
			available_money -= trade->Price*trade_param[trade->InstrumentID].multiplier*(trade_param[trade->InstrumentID].deposit_percent + trade_param[trade->InstrumentID].commission);
		else 				//��ƽ
			available_money += trade->Price*trade_param[trade->InstrumentID].multiplier*(trade_param[trade->InstrumentID].deposit_percent - trade_param[trade->InstrumentID].commission);
	}
	else {
		if (cur_pos < 0) 	//�տ�
			available_money -= trade->Price*trade_param[trade->InstrumentID].multiplier*(trade_param[trade->InstrumentID].deposit_percent + trade_param[trade->InstrumentID].commission);
		else 				//��ƽ
			available_money += trade->Price*trade_param[trade->InstrumentID].multiplier*(trade_param[trade->InstrumentID].deposit_percent - trade_param[trade->InstrumentID].commission);
	}
}

//�����мۼ�������
void FundManager::InMarketEquity(map<string, vector<FT_DATA>> &market_data, string InstrumentID) {
	money_unit cur_equity = equity[equity.size() - 1];
	cur_equity.available_money = available_money;
	cur_equity.total_interest = available_money + abs(net_pos[InstrumentID][net_pos[InstrumentID].size() - 1] * market_data[InstrumentID][market_data[InstrumentID].size() - 1].close * trade_param[InstrumentID].multiplier);
	equity.push_back(cur_equity);
	cout << "Current total_interest is: " << cur_equity.total_interest << endl;
}

