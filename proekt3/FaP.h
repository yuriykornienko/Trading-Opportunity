#pragma once
using namespace std;
#include <iostream>

double fairprice(double basicprice, double stavkacb, int period);

pair<double, double> deltaprice_and_future(double stock_price, int day, double future_price);
