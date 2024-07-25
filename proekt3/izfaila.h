#pragma once
#include <fstream>
#include <iostream>
#include <vector>
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
    Mysecurities(double pricestock, string securit):stock_price(pricestock), securities(securit) {}
    Mysecurities(double futureprice): future_price(futureprice) {}
    Mysecurities(){}
    Mysecurities::Mysecurities(double pricestock, double futureprice, double est, double dafp, double y_in_y, string securit)
    {
        stock_price = pricestock;
        future_price = futureprice;
        estimated_price = est;
        yeld_in_quarter = dafp;
        yeld_in_year = y_in_y;
        securities = securit;
    }
};

vector< Mysecurities> stock_program;

void open_file()
{
    ifstream in_program;
    in_program.open("izfaila1.txt");
    if (in_program.is_open())
    {
        Mysecurities v;
        while (in_program.read((char*)&v, sizeof(Mysecurities)))
        {
            stock_program.push_back(v);
        }
    }
    in_program.close();

    remove("izfaila1.txt");
}

