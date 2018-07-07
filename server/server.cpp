#include "server.h"
#include <sstream>
#include <strstream>

Server::Server() : m_acceptor(m_ser,endpoint_type(boost::asio::ip::tcp::v4(), 6688))
{
    accept();
    m_db = Database();
}

void Server::run(){

    QString a = "CREATE TABLE IF NOT EXISTS warehouse(song TEXT,singer TEXT,album TEXT,downloads BIGINT,sAddress CHAR(200) primary key,lAddress TEXT);";
    m_db.changeDatabase(a);
    a = "CREATE TABLE IF NOT EXISTS download(song TEXT,singer TEXT,album TEXT,personalID TEXT);";
    m_db.changeDatabase(a);
    a = "CREATE TABLE IF NOT EXISTS ilike(song TEXT,singer TEXT,album TEXT,personalID TEXT);";
    m_db.changeDatabase(a);
    a = "CREATE TABLE IF NOT EXISTS personal(ID CHAR(20) primary key,password TEXT);";
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
        std::string c = "select * from warehouse;";
        QString cmd = QString::fromStdString(c);
        std::string returnM = "songListShow "+m_db.selectDatabase(cmd,6);
        do_write(sock,returnM);

    } else if(head == "download") {
        std::string song;
        std::string singer;
        std::string album;
        std::string personalID;
        record >> song >> singer >> album >> personalID;

        std::string c = "INSERT INTO download VALUES('" + song + "','" + singer + "','" + album + "','" + personalID + "');";
        QString cmd = QString::fromStdString(c);
        std::string returnM;
        if(m_db.changeDatabase(cmd))
            returnM = "download ok";
        else
            returnM = "download failed";
        do_write(sock,returnM);

    }else if(head == "upload") {
        std::string sAddress;
        std::string lAddress;
        //        record >> head;
        //        while (head != "|||") {
        //            sAddress += head;
        //            sAddress += " ";
        //            record >> head;
        //        }
        //        record >> head;
        //        while (head != "|||") {
        //            lAddress += head;
        //            lAddress += " ";
        //            record >> head;
        //        }

        while (record >> head) {
            if(head != "|||") {
                sAddress += head;
                sAddress += " ";
            }else break;
        }

        while (record >> head) {
            if(head != "|||") {
                lAddress += head;
                lAddress += " ";
            }else break;
        }


        std::cout << "---" << sAddress << "---" << lAddress << "---";
        std::string c = "INSERT INTO warehouse VALUES('a','b','c','1','" + sAddress + "','" + lAddress + "');";
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
        if(searchforWhat == "song") c = "select * from warehouse where song = '"+ searchContent +"'";
        if(searchforWhat == "singer") c = "select * from warehouse where singer = '"+ searchContent +"'";
        if(searchforWhat == "album") c = "select * from warehouse where album = '"+ searchContent +"'";
        QString cmd = QString::fromStdString(c);
        std::string returnM = "search "+ m_db.selectDatabase(cmd,6);
        do_write(sock,returnM);
    }else if(head == "register") {
        std::string ID;
        std::string password;
        record >> ID >> password;
        std::string c = "INSERT INTO personal VALUES('" + ID + "','" + password + "');";;
        QString cmd = QString::fromStdString(c);
        std::string returnM;
        if(m_db.changeDatabase(cmd))
            returnM = "register ok";
        else
            returnM = "register failed";
        do_write(sock,returnM);
    }else if(head == "login") {
        std::string ID;
        std::string password;
        std::string returnM;
        record >> ID >> password;
        std::string c = "select * from personal where ID = '"+ ID +"' and password = '"+ password +"'" ;
        QString cmd = QString::fromStdString(c);
        if(m_db.selectDatabase(cmd,2).empty())
            returnM = "login failed";
        else
            returnM = "login " + ID;
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
