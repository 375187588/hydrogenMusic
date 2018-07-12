#include "server.h"
#include <sstream>
#include <strstream>
#include <vector>

//-----------s----------
#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/shared_ptr.hpp>


void sender(asio::io_service& io, const char* ip_address, unsigned port, const char* filename)
{
    typedef asio::ip::tcp TCP;

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        std::cerr << "cannot open file\n";
        return;
    }


    boost::shared_ptr<FILE> file_ptr(fp, fclose);

    clock_t cost_time = clock();

    const size_t k_buffer_size = 32 * 1024;
    char buffer[k_buffer_size];
    File_info file_info;

    int filename_size  = strlen(filename) + 1;
    size_t file_info_size = sizeof(file_info);
    size_t total_size = file_info_size + filename_size;
    if (total_size > k_buffer_size) {
        std::cerr << "File name is too long";
        return;
    }
    file_info.filename_size = filename_size;

    fseek(fp, 0, SEEK_END);
    file_info.filesize = ftell(fp);
    rewind(fp);

    memcpy(buffer, &file_info, file_info_size);
    memcpy(buffer + file_info_size, filename, filename_size);

    TCP::socket socket(io);
    socket.connect(TCP::endpoint(asio::ip::address_v4::from_string(ip_address), port));

    std::cout << "Sending file : " << filename << "\n";
    size_t len = total_size;
    unsigned long long total_bytes_read = 0;
    while (true) {
        socket.send(asio::buffer(buffer, len), 0);
        if (feof(fp)) break;
        len = fread(buffer, 1, k_buffer_size, fp);
        total_bytes_read += len;
    }

    cost_time = clock() - cost_time;
    if (cost_time == 0) cost_time = 1;
    double speed = total_bytes_read * (CLOCKS_PER_SEC / 1024.0 / 1024.0) / cost_time;
    std::cout << "cost time: " << cost_time / (double) CLOCKS_PER_SEC  << " s "
              << "  transferred_bytes: " << total_bytes_read << " bytes\n"
              << "speed: " <<  speed << " MB/s\n\n";
}
//-----------e-----------

Server::Server() : m_acceptor(m_ser,endpoint_type(boost::asio::ip::tcp::v4(), 6688))
{
    accept();
    m_db = Database();
}

void Server::run(){
//删除四个表:
//    QString b = "drop table warehouse;";
//    m_db.changeDatabase(b);
//    b = "drop table ilike;";
//    m_db.changeDatabase(b);
//    b = "drop table personal;";
//    m_db.changeDatabase(b);
//    b = "drop table download;";
//    m_db.changeDatabase(b);


    QString a = "CREATE TABLE IF NOT EXISTS warehouse(song TEXT,singer TEXT,album TEXT,nameAr CHAR(50) primary key,downloads BIGINT);";
    m_db.changeDatabase(a);
    a = "CREATE TABLE IF NOT EXISTS download(song TEXT,singer TEXT,album TEXT,nameAr CHAR(50),personalID TEXT,nameArID CHAR(100)  primary key);";
    m_db.changeDatabase(a);
    a = "CREATE TABLE IF NOT EXISTS ilike(song TEXT,singer TEXT,album TEXT,nameAr CHAR(50),personalID TEXT,nameArID CHAR(100)  primary key);";
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
        record >> head;
        std::string c = "select * from " + head + ";";
        QString cmd = QString::fromStdString(c);
        std::string returnM;
        if(head == "warehouse") returnM = "songListShow "+ head + " " +m_db.selectDatabase(cmd,4);
        else if(head == "ilike"){
            record >> head;
            std::string c = "select * from ilike where personalID = '"+ head +"';" ;
            cmd = QString::fromStdString(c);
            returnM = "songListShow ilike " +m_db.selectDatabase(cmd,4);
        } if(head == "download"){
            record >> head;
            std::string c = "select * from download where personalID = '"+ head +"';" ;
            cmd = QString::fromStdString(c);
            returnM = "songListShow download " +m_db.selectDatabase(cmd,4);
        }
        do_write(sock,returnM);

    } else if(head == "download") {
        std::vector<std::string> downloadM;
        std::string temp;
        for(int i=0;i<6;i++) {
            while (record >> head) {
                if(head != "||") {
                    temp += head;
                    temp += " ";
                }else break;
            }
            downloadM.push_back(temp);
            temp.clear();
        }
        //--------------s----------------
        char csong[50];
        int length = downloadM[3].copy(csong,49);
        csong[length-1] = '\0';
        //--------------e----------------------
        std::string c = "INSERT INTO download VALUES('" + downloadM[0] + "','" + downloadM[1] + "','" + downloadM[2] + "','" + downloadM[3] + "','" + downloadM[4] + "','" + downloadM[5] + "');";
        QString cmd = QString::fromStdString(c);
        std::string returnM;
        if(m_db.changeDatabase(cmd)) {
            c= "update warehouse set downloads=downloads+1 where nameAr='" +downloadM[5]+"';";
            QString cmd = QString::fromStdString(c);
            m_db.changeDatabase(cmd);
            returnM = "download ok";
        }else
            returnM = "download failed";
        do_write(sock,returnM);
        //------------s------------------
        //sender(m_ser, "127.0.0.1",1345, "脸红的思春期 - You(=I).mp3");


        std::cout << "lll"<< downloadM[3] << "lll"<< std::endl;
        //std::cout << sock->remote_endpoint().address();
        char caddress[50];
        std::string address = sock->remote_endpoint().address().to_string();

        int length1 = address.copy(caddress,49);
        caddress[length1] = '\0';
        //---------------s-------------
        char s_source[100]="../server/source/song/";
        strcat(s_source, csong);

        //-----------------e---------------
        sender(m_ser, caddress,1345, s_source);
        //------------e---------------------

    }else if(head == "upload") {

        std::vector<std::string> songM;
        std::string temp;
        for(int i=0;i<4;i++) {
            while (record >> head) {
                if(head != "||") {
                    temp += head;
                    temp += " ";
                }else break;
            }
            songM.push_back(temp);
            temp.clear();
        }

        std::cout << songM[0] << songM[1]<< songM[2]<< songM[3]<< std::endl;
        std::string c = "INSERT INTO warehouse VALUES('" + songM[0] + "','" + songM[1] + "','" + songM[2] + "','" + songM[3] + "','0');";
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
        record >> searchforWhat;
        while (record >> head) {
            searchContent += head;
            searchContent += " ";
        }
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
    }else if(head == "ilike") {
        std::vector<std::string> ilikeM;
        std::string temp;
        for(int i=0;i<6;i++) {
            while (record >> head) {
                if(head != "||") {
                    temp += head;
                    temp += " ";
                }else break;
            }
            ilikeM.push_back(temp);
            temp.clear();
        }
        std::string c = "INSERT INTO ilike VALUES('" + ilikeM[0] + "','" + ilikeM[1] + "','" + ilikeM[2] + "','" + ilikeM[3] + "','" + ilikeM[4] + "','" + ilikeM[5] + "');";
        QString cmd = QString::fromStdString(c);
        std::string returnM;
        if(m_db.changeDatabase(cmd))
            returnM = "ilike ok";
        else
            returnM = "ilike failed";
        do_write(sock,returnM);

    }else if(head == "delete") {
        //dislike是从歌词界面取消喜欢，ilike是从我喜欢列表里取消喜欢
        record >> head;
        std::string c;
        QString cmd;
        std::string returnM;
        std::string head1;
        std::string head2;
        if(head == "dislike" || head == "ilike")  {
            while (record >> head2) {
                head1 += head2;
                head1 += " ";
            }
            c = "delete from ilike where nameArID='"+ head1 +"';";
            cmd = QString::fromStdString(c);
            if(head == "dislike") {
                std::cout << c << std::endl;
                if(m_db.changeDatabase(cmd))
                    returnM = "delete ilike ok";
                else
                    returnM = "delete ilike failed";
            }else{
                if(m_db.changeDatabase(cmd))
                    returnM = "delete ilikes ok";
                else
                    returnM = "delete ilikes failed";
            }
        }else if(head == "download"){
            while (record >> head2) {
                head1 += head2;
                head1 += " ";
            }
            c = "delete from download where nameArID='"+ head1 +"';";
            cmd = QString::fromStdString(c);
            if(m_db.changeDatabase(cmd))
                returnM = "delete download ok";
            else
                returnM = "delete download failed";
        }
        do_write(sock,returnM);
    }else if(head == "tourists"){
        std::string c = "select * from personal where password = '**********'" ;
        QString cmd = QString::fromStdString(c);
        std::string ret =m_db.selectDatabase(cmd,1);
        std::istringstream r(ret);
        std::vector<std::string> t;
        std::string returnM;
        int i=0;
        while(r >> head) {
            if(head != "||" && head != "|||") {
                t.push_back(head);
                std::cout << head << std::endl;
                i++;
            }
        }
        std::string id = "***" + std::to_string(i+1);
        c = "INSERT INTO personal VALUES('" + id + "','**********');";;
        cmd = QString::fromStdString(c);
        if(m_db.changeDatabase(cmd)){
            returnM = "tourists " + id;
        }
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
