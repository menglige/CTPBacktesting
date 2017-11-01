// CTPBacktesting.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DBReader.h"
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <deque>
#include <string>
using namespace std;

std::condition_variable empty_signal;			//报单队列是否为空
std::mutex mtx;									//全局锁
deque<ORDER> order_queue;

int main()
{
	DBReader *dr = new DBReader();
	delete dr;
    return 0;
}

