#include "Future.h"

pair<string, int> datayearfuture() {

    time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int today = now->tm_mday;
    int month = (now->tm_mon + 1);
    int year = (now->tm_year + 1900);

    string yearchar;
    int syear = year % 10;
    yearchar = to_string(syear);

    string charfuture;
    if (month == 1 || month == 2 || month == 3 && today <= 15 || month == 12 && today > 16) {
        charfuture = "H";
    }
    if (month == 4 || month == 5 || month == 3 && today > 16 || month == 6 && today <= 15) {
        charfuture = "M";
    }
    if (month == 7 || month == 8 || month == 6 && today > 16 || month == 9 && today <= 15) {
        charfuture = "U";
    }
    if (month == 10 || month == 11 || month == 9 && today > 16 || month == 12 && today <= 15) {
        charfuture = "Z";
    }

    string datayear = charfuture + yearchar;

    struct tm timeinfo = { 0 };     // структура даты и времени
    timeinfo.tm_year = year - 1900;         // корректируем год
    timeinfo.tm_mon = month - 1;            // корректируем значение мес€ца
    timeinfo.tm_mday = today;                   // введЄнный день

    time_t rawtime = mktime(&timeinfo);
    int today_sec = rawtime; //вычисленеи секунд до текущей даты 

    struct tm timeinfo_expiration = { 0 };
    if (charfuture == "M") {
        timeinfo_expiration.tm_year = year - 1900;
        timeinfo_expiration.tm_mon = 5;
        timeinfo_expiration.tm_mday = 15;
    }

    if (charfuture == "U") {
        timeinfo_expiration.tm_year = year - 1900;
        timeinfo_expiration.tm_mon = 8;
        timeinfo_expiration.tm_mday = 15;

    }

    if (charfuture == "Z") {
        timeinfo_expiration.tm_year = year - 1900;
        timeinfo_expiration.tm_mon = 11;
        timeinfo_expiration.tm_mday = 15;

    }

    if (charfuture == "H") {
        if (month == 12) {
            timeinfo_expiration.tm_year = year - 1899;
            timeinfo_expiration.tm_mon = 2;
            timeinfo_expiration.tm_mday = 15;

        }
        else {
            timeinfo_expiration.tm_year = year - 1900;
            timeinfo_expiration.tm_mon = 2;
            timeinfo_expiration.tm_mday = 15;
        }

    }

    time_t rawtime_expiration = mktime(&timeinfo_expiration);
    int experetion_sec = rawtime_expiration;

    int rezalt_day_experetion = (experetion_sec - today_sec) / 86400;//rde

    pair <string, int> pair_rezult;
    pair_rezult = make_pair(datayear, rezalt_day_experetion);


    return  pair_rezult;
}

double getfieldfromjsonfuture(string json, string namesecuritis) {

    stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);
    boost::property_tree::ptree& b = root.get_child("marketdata");
    boost::property_tree::ptree& c = b.get_child("data");

    string rezaltprom;

    int i = 0;
    BOOST_FOREACH(boost::property_tree::ptree::value_type & rowpair, c.get_child(""))
    {
        BOOST_FOREACH(boost::property_tree::ptree::value_type & itempair, rowpair.second) {
            if (i == 8) {
                rezaltprom = itempair.second.get_value<std::string>();
                break;
            }
            ++i;
        }
    }
    double rezalt = stoi(rezaltprom);

    return  rezalt;
};

string ClientFuture::getresponse(string ip)
{
    int x = 0;
    boost::asio::io_context io;
    boost::asio::ip::tcp::resolver resolver(io);
    boost::asio::ip::tcp::socket socket(io);
    boost::asio::connect(socket, resolver.resolve(main_apifuture, "80"));
    string argument13 = argum_apifuture + ip;
    http::request<http::string_body> req(http::verb::get, argument13, 10);

    req.set(http::field::host, main_apifuture);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(socket, req);
    string responce;

    {
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket, buffer, res);
        responce = boost::beast::buffers_to_string(res.body().data());
    }

    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    return responce;
}
