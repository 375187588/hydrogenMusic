#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include "boost/thread.hpp"
#include <iostream>
#include <QObject>
//---------s----------
//#include "file_info.h"
//#include "receiver.h"
//#include <string>
//---------e--------
#define LENGTH 1024

class Client/*:public QObject*/
{
public:
//    Client(QObject *parent = 0):QObject(parent){}
    Client(boost::asio::io_service &ios);

    void doWrite(std::string s, std::string &receiveMessage);
    void doCommand(std::string &receiveMeaasge);
    void rbufClear();//清空read_str
    void wbufClear();//清空write_str
    void copystrAll(std::string l);//复制l到read_str

    void onConnect(const boost::system::error_code & err);
    void download(char *filename);
private:
    void stop();
    boost::asio::ip::tcp::socket m_sock;
    boost::asio::ip::tcp::endpoint m_ep;
    char rbuf[LENGTH];
    char wbuf[LENGTH];
};

#endif // CLIENT_H
