#include <iostream>
#include "Stock.h"
#include "Future.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <fstream>
#include <boost/foreach.hpp>
#include <vector>
#include <thread>
#include "FaP.h"
#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
using namespace std;

class Mysecurities {

public:
    double stock_price;
    double future_price;
    double estimated_price;
    double yeld_in_quarter;
    double yeld_in_year;
    string securities;
public:
    Mysecurities(double pricestock, string securit) : stock_price(pricestock), securities(securit) {}
    Mysecurities(double futureprice) : future_price(futureprice) {}

};

void potok_stock()
{
    vector<string> mytradelist = { "LKOH", "SBER", "ROSN", "GAZP" };
    vector<string> mytradelistjson = { ".json" };
     ClientStock client;
         for (size_t i = 0; i < mytradelist.size(); i++)
    {
        string res = client.getresponse((mytradelist[i] + mytradelistjson[0]));
    };
};

 vector< Mysecurities> stock;

int wain()
{
   vector<string> mytradelist = { "LKOH", "SBER", "ROSN", "GAZP" };
   vector<string> mytradelistjson = { ".json" };

    ClientStock client;
    for (size_t i = 0; i < mytradelist.size(); i++)
    {
        string res = client.getresponse((mytradelist[i] + mytradelistjson[0]));
        stock.push_back(Mysecurities(getfieldfromjson(res, mytradelist[i]), mytradelist[i])); 
    };
  
    vector<string> mytradelistfuture = { "LK", "SR", "RN", "GZ" };
    pair <string, int> dataandyear = datayearfuture();
    vector<string> mytradelistjsonfuture = { ".json" };

    ClientFuture futres;
    for (size_t k = 0; k < mytradelistfuture.size(); k++)
    {
        string res = futres.getresponse((mytradelistfuture[k] + dataandyear.first + mytradelistjsonfuture[0]));
        stock[k].future_price = (getfieldfromjsonfuture(res, mytradelistfuture[k]));
    }
    
    double stavkacb = 0.17;
    int rde = dataandyear.second;

    for (size_t q = 0; q < stock.size(); q++)
    {
        if (q == 0) {
            stock[q].estimated_price = fairprice(stock[q].stock_price * 10, stavkacb, rde);
        }
        else
            stock[q].estimated_price = fairprice(stock[q].stock_price * 100, stavkacb, rde);
    }

    for (size_t o = 0; o < stock.size(); o++)
    {
       if (o == 0 )
        {
            auto rezalt_yeld = deltaprice_and_future(stock[o].stock_price * 10, rde, stock[o].future_price);
            stock[o].yeld_in_quarter = rezalt_yeld.first;
            stock[o].yeld_in_year = rezalt_yeld.second;
        }
        else 
        {
            auto rezalt_yeld = deltaprice_and_future(stock[o].stock_price * 100, rde, stock[o].future_price);
            stock[o].yeld_in_quarter = rezalt_yeld.first;
            stock[o].yeld_in_year = rezalt_yeld.second;
        }
      
    }

    ofstream out;
    out.open("izfaila1.txt");
    for (size_t i = 0; i < stock.size(); i++)
    {
        out.write((char*)&stock[i], sizeof(Mysecurities));
    }
    out.close();

    return 0;
}
