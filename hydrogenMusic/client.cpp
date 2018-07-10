#include "client.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iostream>
#include "myerror.h"

using namespace boost::asio;
using namespace std;

Client::Client(boost::asio::io_service &ios):m_sock(ios)
{
    std::cout << "client start." << std::endl;
        m_ep = ip::tcp::endpoint(ip::address::from_string("127.0.0.1"),6688);
//    m_sock.asy_connect(m_ep);//连接时执行,完成后执行onconnect
    m_sock.async_connect(m_ep,boost::bind(&Client::onConnect,this,_1));
}

void Client::onConnect(const boost::system::error_code &err)
{
    if(err) stop();
}

void Client::doWrite(std::string s,std::string &receiveMessage)
{
    wbufClear();
    for(int i = 0;i != 1024;i++) {
        if(i < s.size()) wbuf[i] = s[i];
        else wbuf[i] = '\0';
    }
    std::cout << "write" << std::endl;
    write(m_sock,boost::asio::buffer(wbuf));
    doCommand(receiveMessage);
}

void Client::doCommand(std::string &receiveMeaasge)
{
    rbufClear();
    std::cout << "read" << std::endl;
    size_t readSize = 0;
    while(readSize == 0) {
//        boost::system::error_code ec;
        readSize = m_sock.read_some(buffer(rbuf)/*,ec*/);
    }
    string s(rbuf);
    std::cout  << "receive:" << s << endl;
    receiveMeaasge = s;
}

void Client::rbufClear()
{
    for(int i = 0;i != LENGTH;i++) {
        rbuf[i] = '\0';
    }
}
void Client::wbufClear()
{
    for(int i = 0;i != LENGTH;i++) {
        wbuf[i] = '\0';
    }
}

void Client::copystrAll(string l)//只能输入LENGTH-1个字符
{
    if(l.size() < LENGTH)
    {
        for(size_t i = 0; i != l.size(); ++i)
        {
            rbuf[i] = l[i];
        }
        rbuf[l.size()]='\0';
    }
}

void Client::stop()
{
    m_sock.close();
}
