#include "stdafx.h"
#include "Dealer.h"

Dealer::Dealer(vector<string> &instrument_array) {
	//ע���Ϻ�Լ�б�
	for (int i = 0; i < instrument_array.size(); i++) {
		ctp_order.insert(make_pair(instrument_array[i], map<int,ORDER>()));
		cout << "Dealer-->Register Instrument: " << instrument_array[i] << endl;
	}

	//����ɽ����ͱ�����Ϣ
	my_trade = new MyTrade();
	my_order = new MyOrder();
}

Dealer::~Dealer() {
	delete my_strategy, my_trade, my_order;
}

void Dealer::Register(MyStrategy *strategy) {
	my_strategy = strategy;
}

//�������������ض���-->����������
void Dealer::OrderAction() {
	if (order_queue.size() == 0) 
		return;

	while (order_queue.size() > 0) {
		//�ز�ϵͳ�ڴ�����ʱ�ص�OnRtnOrder����
		strcpy_s(my_order->OrderSysID, "999");
		my_order->FrontID = 100;
		my_order->SessionID = 100;
		strcpy_s(my_order->OrderRef, order_queue[0].ORDER_REF);
		my_order->Direction = order_queue[0].direction;
		my_order->OrderStatus = order_queue[0].order_type == ORDER_COMMIT ? '3' : '5';
		strcpy_s(my_order->StatusMsg, "̫6��");
		my_order->MinVolume = 1;	//Ĭ����С��λһ��

		//ģ�ⱨ�ͽ���������
		if (order_queue[0].order_type == ORDER_COMMIT) {
			my_strategy->UpdateOnRtnOrder(my_order, true);
			my_strategy->OnRtnOrder(my_order);
			ctp_order[order_queue[0].id].insert(make_pair(atoi(order_queue[0].ORDER_REF), order_queue[0]));
			cout << "Current queue size: " << ctp_order[order_queue[0].id].size() << endl;
		}
		else if (order_queue[0].order_type == ORDER_CANCEL) {
			my_strategy->UpdateOnRtnOrder(my_order, false);
			my_strategy->OnRtnOrder(my_order);
			ctp_order[order_queue[0].id].erase(atoi(order_queue[0].ORDER_REF));
			cout << "Current queue size: " << ctp_order[order_queue[0].id].size() << endl;
		}
		else {
			cout << "Unknown order type!" << endl;
		}

		//ɾ����ǰ�Ѵ�����
		order_queue.pop_front();
	}

}

//�гɽ�
//��һ�汣���жϣ����նԼ۳ɽ�
void Dealer::Strike(map<string, vector<FT_DATA>> &market_data, string InstrumentID) {
	size_t cur_idx = market_data[InstrumentID].size() - 1;
	int pos_change = 0;
	for (map<int, ORDER>::iterator order = ctp_order[InstrumentID].begin(); order != ctp_order[InstrumentID].end();) {
		if (order->second.direction=='0' && order->second.price >= market_data[InstrumentID][cur_idx].ask1 || order->second.direction == '1' && order->second.price <= market_data[InstrumentID][cur_idx].bid1) {
			//��ǰ�������Գɽ��������ٵ���
			strcpy_s(my_trade->InstrumentID, InstrumentID.c_str());
			my_trade->Price = order->second.direction == '0' ? min(order->second.price, market_data[InstrumentID][cur_idx].ask1) : max(order->second.price, market_data[InstrumentID][cur_idx].bid1);
			my_trade->Direction = order->second.direction;
			my_trade->Volume = order->second.volume;
			pos_change += (order->second.direction == '0' ? 1 : -1);
			my_strategy->UpdateOnRtnTrade(my_trade);	
			my_strategy->OnRtnTrade(my_trade);
			ctp_order[InstrumentID].erase(order++);
		}
		else {
			order++;
		}
	}
	//���¾��ֲ�
	net_pos[InstrumentID].push_back(net_pos[InstrumentID][net_pos[InstrumentID].size() - 1] + pos_change);
}