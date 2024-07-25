#include "Stock.h"

double getfieldfromjson(string json, string namesecuritis) {

    stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);
    boost::property_tree::ptree& b = root.get_child("marketdata");
    boost::property_tree::ptree& c = b.get_child("data");

    string rezalt_prom;

    int i = 0;
    BOOST_FOREACH(boost::property_tree::ptree::value_type & rowpair, c.get_child(""))
    {
        BOOST_FOREACH(boost::property_tree::ptree::value_type & itempair, rowpair.second) {
            if (i == 12) {
                rezalt_prom = itempair.second.get_value<std::string>();
                break;
            }
            ++i;
        }
    }
    double rezalt = stod(rezalt_prom);
    return  rezalt;
};

string  ClientStock::getresponse(string ip)
{
    int x = 0;
    boost::asio::io_context io;
    boost::asio::ip::tcp::resolver resolver(io);
    boost::asio::ip::tcp::socket socket(io);
    boost::asio::connect(socket, resolver.resolve(main_api, "80"));
    string argument = argum_api + ip;
    http::request<http::string_body> req(http::verb::get, argument, 10);
    req.set(http::field::host, main_api);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(socket, req);
    string responce;

    boost::beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);
    responce = boost::beast::buffers_to_string(res.body().data());

    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    return responce;
};

