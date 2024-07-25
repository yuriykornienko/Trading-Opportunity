#pragma once
#include <iostream>
#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <ctime>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;

pair<string, int> datayearfuture();

const static string main_apifuture = "iss.moex.com";
const static string argum_apifuture = "/iss/engines/futures/markets/forts/securities/";
namespace http = boost::beast::http;

double getfieldfromjsonfuture(string json, string namesecuritis);

class ClientFuture {
public:
    string getresponse(string ip);
};

