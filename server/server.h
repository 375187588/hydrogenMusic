#ifndef SERVER_H
#define SERVER_H

#include <boost/thread.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/pthread/thread_data.hpp>
#include <cctype>
#include <cstdlib>
#include <stack>
#include <sstream>

#include "control.h"
#include "file_info.h"

class Server
{
    typedef Server this_type;
    typedef boost::asio::ip::tcp::acceptor acceptor_type;
    typedef boost::asio::ip::tcp::endpoint endpoint_type;
    typedef boost::asio::ip::tcp::socket socket_type;
    typedef boost::asio::ip::address address_type;
    typedef boost::shared_ptr<socket_type> sock_ptr;



private:
    boost::asio::io_service m_ser;

    acceptor_type m_acceptor;
    char m_rdbuf[1024]; //数组
    char m_wtbuf[1024];
    Control m_db;

public:
    Server();
    void run();
    void accept();
    void accept_handler(const boost::system::error_code& ec, sock_ptr sock);
    void do_read(sock_ptr sock);
    void read_handler(const boost::system::error_code&ec, sock_ptr sock);
    void do_write(sock_ptr sock, std::string result);
    void write_hander(const boost::system::error_code&ec, sock_ptr sock);
    void rdbufClear();
    QString strToQst(std::string s);
    ~Server();

    //数据库执行操作
    bool doRegister(std::string username,std::string password);//注册
    bool doLogin(std::string username,std::string password);//登录
    bool doPublishOrder(std::istringstream &record);//发布订单

};

#endif // SERVER_H
