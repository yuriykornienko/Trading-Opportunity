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
using namespace std;

const static string main_api = "iss.moex.com"; 
const static string argum_api = "/iss/engines/stock/markets/shares/boards/TQBR/securities/";
namespace http = boost::beast::http;

double getfieldfromjson(string json, string namesecuritis);

class ClientStock {
public:
    string getresponse(string ip);
};






