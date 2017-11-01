#include "stdafx.h"
#include "DBReader.h"
#include <string>

//�������ݿ�readerʵ������ʼ����Լ�б�
DBReader::DBReader() {
	ifstream future_reader(BACKTEST_INSTRUMENT);
	if (future_reader.is_open()) {
		string tvar;
		getline(future_reader, tvar);
		for (int i = 0; i < atoi(tvar.c_str()); i++) {
			string instrument;
			getline(future_reader, instrument);
			instrument_array.push_back(instrument);
		}
	}
	future_reader.close();
}

void DBReader::Register(MyStrategy *strategy) {
	my_strategy = strategy;
}

DBReader::~DBReader() {
	delete my_db, my_strategy;
}