#include "server.h"
#include <sstream>
#include <strstream>

Server::Server() : m_acceptor(m_ser,endpoint_type(boost::asio::ip::tcp::v4(), 6688))
{
    accept();
    m_db = Database();
}

void Server::run(){

    QString a = "CREATE TABLE IF NOT EXISTS songList(nameAr CHAR(60) primary key,address TEXT);";
    m_db.changeDatabase(a);
    a = "CREATE TABLE IF NOT EXISTS downLoad(nameAr CHAR(20) primary key,address TEXT);";
    m_db.changeDatabase(a);
    m_ser.run();
}

void Server::accept()
{
    sock_ptr sock(new socket_type(m_ser));
    m_acceptor.async_accept(*sock, boost::bind(&this_type::accept_handler, this, boost::asio::placeholders::error, sock));
}

void Server::accept_handler(const boost::system::error_code& ec, sock_ptr sock)
{
    if (ec) return;

    std::cout<<"Client:";
    std::cout<< sock->remote_endpoint().address() << "  " << sock->remote_endpoint().port()<<std::endl;
    do_read(sock);
    accept();
}


void Server::do_read(sock_ptr sock)
{
    rdbufClear();
    async_read(*sock,boost::asio::buffer(m_rdbuf),
               boost::bind(&Server::read_handler,this,boost::asio::placeholders::error,sock));


}

void Server::read_handler(const boost::system::error_code&ec,sock_ptr sock)
{
    if (ec)
    {
        return;
    }
    std::string m;
    int length = 0;
    for(int i = 0;i != 1024;i++) {
        if(m_rdbuf[i] != '\0')
            length = i;
    }
    for(int i = 0;i != length + 1;i++) {
        m.push_back(m_rdbuf[i]);
    }
    std::cout << m << std::endl;
    std::istringstream record(m);
    std::string head;
    record >> head;
    if(head == "songListShow") {
        std::string c = "select * from songList;";
        QString cmd = QString::fromStdString(c);
        std::string returnM = "songListShow "+m_db.selectDatabase(cmd,2);
        do_write(sock,returnM);

    } else if(head == "download") {
        std::string nameAr;
        std::string addr;
        record >> nameAr;
        while (record >> head) {
            addr += head;
        }
        std::string c = "INSERT INTO downLoad VALUES('" + nameAr + "','" + addr + "');";
        QString cmd = QString::fromStdString(c);
        std::string returnM;
        if(m_db.changeDatabase(cmd))
            returnM = "download ok";
        else
            returnM = "download failed";
        do_write(sock,returnM);

    }else if(head == "upload") {
        std::string nameAr;
        std::string addr;
        record >> nameAr;
        while (record >> head) {
            addr += head;
        }
        std::string c = "INSERT INTO songList VALUES('" + nameAr + "','" + addr + "');";
        QString cmd = QString::fromStdString(c);
        std::string returnM;
        if(m_db.changeDatabase(cmd))
            returnM = "upload ok";
        else
            returnM = "upload failed";
        do_write(sock,returnM);
    }else if(head == "search") {
        std::string searchContent;
        std::string searchforWhat;
        std::string c;
        record >> searchContent >> searchforWhat;
        if(searchforWhat == "nameAr") c = "select * from songList where nameAr = '"+ searchContent +"'";
        QString cmd = QString::fromStdString(c);
        std::string returnM = "search "+ m_db.selectDatabase(cmd,2);
        do_write(sock,returnM);
    }

}


void Server::rdbufClear()
{
    for(int i = 0;i != 1024;i++)
        m_rdbuf[i] = '\0';
}

void Server::do_write(sock_ptr sock,std::string result)
{
    for(int i = 0;i != 1024;i++) {
        if(i < result.size())
            m_wtbuf[i] = result[i];
        else m_wtbuf[i] = '\0';
    }
    std::cout << result << std::endl;
    async_write(*sock,boost::asio::buffer(m_wtbuf),
                boost::bind(&Server::write_hander, this, boost::asio::placeholders::error, sock));
}

void Server::write_hander(const boost::system::error_code&ec, sock_ptr sock)
{
    if(ec)
    {
        return;
    }

    do_read(sock);
}

Server::~Server()
{

}
