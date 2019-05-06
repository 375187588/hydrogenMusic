#include "control.h"
#include <sstream>
#include <iostream>
#include <QJSValue>
#include <QUrl>
#include <vector>
#include <time.h>
#include "personalinfo.h"
#include "song.h"
#include "treat.h"
void Control::run()
{
    m_io.run();
    std::cout << "run" << std::endl;
}

void Control::sendMessage(QString m)
{
    m_sendMessage = m;
    m_client.doWrite(m_sendMessage.toStdString(),m_receiveMessage);
    std::istringstream record(m_receiveMessage);
    std::string head;
    std::string head1;
    record >> head;
    if(head == "songListShow") {
        record >> head1;
        std::string ret;
        ret = m_receiveMessage.substr(head.length() + head1.length() +2);
        m_songlis = detach(ret);
        if(head1 == "warehouse") {
            m_songlis = detach(ret);
            emit songList();
        }
        else if(head1 == "ilike") {
            personalInfo->m_ilik = detach(ret);
            emit ilikeShow();
        }
        else if(head1 == "download") {
            personalInfo->m_downloa = detach(ret);
            emit downloadShow();
        }else{
            personalInfo->m_tempSheet = detach(ret);
            emit sheetListShow(QString::fromStdString(head1));
        }
    }else if(head == "songsheet") {
        std::string head1;
        record >> head1;
        std::string ret;
        ret = m_receiveMessage.substr(head.length() + head1.length() +2);
        if(head1 == "all"){
            personalInfo->m_songSheet = detachToQstring(ret);
            emit songsheetAll();
        }else if(head1 == "add"){
            emit songsheetAddOk(QString::fromStdString(ret));
            sendMessage("songsheet all "+personalInfo->m_ID);
        }else if(head1 == "addsong"){
            emit songsheetAddSongOk(QString::fromStdString(ret));
        }
    }else if(head == "songsheet") {

    }else if(head == "sheetinfo") {
        std::string ret;
        ret = m_receiveMessage.substr(head.length()+1);
        emit sheetInfo(detachToQstring(ret));
    }
    else if(head == "treat") {
        record >> head;
        std::string ret;
        if(head == "send"){
            record >> ret;
            emit sendtreatOk(QString::fromStdString(ret));
        }else if(head == "all"){
            ret = m_receiveMessage.substr(10);
            m_treat = detachToTreat(ret);
            emit treatShow();
            emit uploadOk();
        }
    }
    else if(head == "download") {
        std::string ret;
        record >> ret;
        if(ret == "ok") emit downloadOk();
    }else if(head == "upload") {
        std::string ret;
        record >> ret;
        if(ret == "ok") {
            emit uploadOk();
            sendMessage("songListShow warehouse");
        }
    }else if(head == "search") {
        std::string ret;
        ret = m_receiveMessage.substr(head.length()+1);
        m_searc = detach(ret);
        emit searchOk();
    }else if(head == "register") {
        std::string ret;
        record >> ret;
        if(ret == "ok") emit registerOk();
        else emit registerFailed();
    }else if(head == "login") {
        std::string ret;
        record >> ret;
        if(ret == "failed") {
            emit loginFailed();
        }else {
            record >> ret;
            personalInfo = new PersonalInfo();
            personalInfo-> m_ID = QString::fromStdString(ret);
            emit loginOk();
        }
    }else if(head == "ilike") {
        std::string ret;
        record >> ret;
        if(ret == "ok") {
            sendMessage("songListShow ilike " + personalInfo-> m_ID);
            emit ilikeOk();
        }
    }else if(head == "delete") {
        std::string ret;
        record >> ret;
        if(ret == "ilike") {
            record >> ret;
            if(ret == "ok") {
                sendMessage("songListShow ilike " + personalInfo-> m_ID);
                emit dislike();
            }
        }else if(ret == "ilikes") {
            record >> ret;
            if(ret == "ok") sendMessage("songListShow ilike " + personalInfo-> m_ID);
        }else if(ret == "download") {
            record >> ret;
            if(ret == "ok") sendMessage("songListShow download " + personalInfo-> m_ID);
        }else{
            std::string ret1;
            record >> ret1;
            if(ret1 == "ok") sendMessage("songListShow " + QString::fromStdString(ret) +" "+ personalInfo-> m_ID);
        }
    }else if(head == "tourists") {

        std::string ret;
        record >> ret;
        personalInfo = new PersonalInfo();
        personalInfo-> m_ID = QString::fromStdString(ret);
        emit touristsloginOk();
    }

}

QList<QString> Control::returnInfo(QString url)
{
    printf("into Control::return n=info\n");
    printf("-------------\n");
    std::cout<<url.toStdString()<<std::endl;

    //    QByteArray ba = url.toLatin1();
    //    char *ch=ba.data();

    //    int len = p.length();
    //    char *ch = (char *)malloc(len * sizeof(char));
    //    p.copy(ch, len, 0);

    char ch[100] = "\0";
    std::string p = url.toStdString();
    int i;
    for(i = 0; i < p.length(); i++)
    {
        ch[i] = p[i];
    }
    ch[i] = '\0';


    std::vector<std::string> v = media->get_song_infos(ch);
    if(!v.empty())
    {
        printf("v is not empty\n");
    }else{
        printf("v is  empty\n");
    }

    for(auto &l:v)
    {
        std::cout<<"v elements is "<<l<<std::endl;
    }

    QList<QString> l;
    l.append(QString::fromStdString(v[0]));
    l.append(QString::fromStdString(v[1]));
    if(v.size()>=3) l.append(QString::fromStdString(v[2]));
    std::cout <<l[0].toStdString()<<l[1].toStdString();
    if(v.size()>=3) std::cout <<l[2].toStdString();
    std::cout << std::endl;
    return l;

}

bool Control::isIlike(QString nameAr)
{
    if(personalInfo->m_ilik.length() > 0) {
        for (int i = 0;i<personalInfo->m_ilik.length();i++) {
            if(personalInfo->m_ilik[i]->m_key == nameAr) {
                return true;
            }
        }
    }
    return false;
}

QList<Song *> Control::detach(std::string ret)
{
    QList<QString> vec;
    QList<Song *> v;
    if(ret.empty()) return v;

    std::istringstream rec(ret);
    std::string temp1;
    std::string temp2;

    while(rec >> temp1) {
        if(temp1 != "||" && temp1 != "|||" ) {
            temp2 +=temp1;
            temp2 +=" ";
        }else {
            if(!temp2.empty()) {
                temp2 = temp2.substr(0,temp2.length()-1);
                vec.append(QString::fromStdString(temp2));
                temp2.clear();
            }
        }
    }
    int n = vec.length()/4;
    for(int i=0;i<n;i++)
    {
        if(!vec.empty())
        {
            QString songName = vec.front();
            vec.pop_front();
            QString singer = vec.front();
            vec.pop_front();
            QString album = vec.front();
            vec.pop_front();
            QString key = vec.front();
            vec.pop_front();
            v.append(new Song(songName,singer,album,key));
        }
    }
    return v;
}

QList<QString> Control::detachToQstring(std::string ret)
{
    QList<QString> vec;
    if(ret.empty()) {
        return vec;
    }
    std::istringstream rec(ret);
    std::string temp1;
    std::string temp2;

    while(rec >> temp1) {
        if(temp1 != "||" && temp1 != "|||" ) {
            temp2 +=temp1;
            temp2 +=" ";
        }else {
            if(!temp2.empty()) {
                temp2 = temp2.substr(0,temp2.length()-1);
                vec.append(QString::fromStdString(temp2));
                temp2.clear();
            }
        }
    }
    return vec;
}

QList<Treat *> Control::detachToTreat(std::string ret)
{
    QList<QString> vec;
    QList<Treat *> v;
    if(ret.empty()) return v;

    std::istringstream rec(ret);
    std::string temp1;
    std::string temp2;

    while(rec >> temp1) {
        if(temp1 != "||" && temp1 != "|||" ) {
            temp2 +=temp1;
            temp2 +=" ";
        }else {
            if(!temp2.empty()) {
                temp2 = temp2.substr(0,temp2.length()-1);
                vec.append(QString::fromStdString(temp2));
                temp2.clear();
            }
        }
    }
    int n = vec.length()/7;
    for(int i=0;i<n;i++)
    {
        if(!vec.empty())
        {
            QString id = vec.front();
            vec.pop_front();
            QList<QString> song;
            song.append(vec.front());
            vec.pop_front();
            song.append(vec.front());
            vec.pop_front();
            song.append(vec.front());
            vec.pop_front();
            song.append(vec.front());
            vec.pop_front();

            QString text = vec.front();
            vec.pop_front();
            QString time = vec.front();
            vec.pop_front();
            v.append(new Treat(id,text,song,timeTransf(time)));
        }
    }
    return v;
}

QString Control::timeTransf(QString time)
{
    time_t ti;               //声明time_t类型变量
    std::istringstream is(time.toStdString());
    is >> ti;

    tm *t =localtime(&ti);
    int month = t->tm_mon + 1;
    std::string s = std::to_string(month) + "月"+std::to_string(t->tm_mday)+"日";
    return QString::fromStdString(s);
}

bool Control::addToL(QString songName,QString singer,QString album,QString key)
{
    Song *l = new Song(songName,singer,album,key);
    for(int i = 0;i<m_playlist.length();i++)
        if(m_playlist[i]->m_key == l->m_key) return false;
    m_playlist.push_back(l);
    return true;


}

void Control::deleteInPlaylist(int index)
{
    for(int j = index;j!=m_playlist.length()-1;j++) {
        if(j!=m_playlist.length()-1) {
                m_playlist[j] = m_playlist[j+1];
        }
    }
        m_playlist.pop_back();
    emit playlistChange();
}

void Control::upList(int index)
{
    Song *temp = m_playlist[index];

    for(int j = index;j!=-1;j--) {
        if(j!=0) {
            m_playlist[j] = m_playlist[j-1];
        }else{
            m_playlist[j] = temp;
        }
    }
    emit playlistChange();

}

QList<QString> Control::nextSong(int model, int index)
{

    QList<QString> l;
    int returnIndex=0;
    switch (model) {
    case 0: //shun xu
        if(index != m_playlist.length()-1) returnIndex = index+1;
        break;
    case 1://sui ji
        srand((unsigned int)time(0));
        returnIndex = rand() % (m_playlist.length());
        break;
    case 2://dan qu xun huan
        returnIndex =  index;
        break;
    }

    if(m_playlist[returnIndex]) {
        l.append(m_playlist[returnIndex]->songName());
        l.append(m_playlist[returnIndex]->singer());
        l.append(m_playlist[returnIndex]->album());
        l.append(m_playlist[returnIndex]->key());
        return l;
    }else return l;
}

int Control::currentSong(QString nameArID)
{
    if(m_playlist.length() > 0) {
        for (int i = 0;i<m_playlist.length();i++) {
            QString temp = m_playlist[i]->m_key ;
            if(temp == nameArID) {
                return i;
            }
        }
    }else
        return 0;
}
void fsender(asio::io_service& io, const char* ip_address, unsigned port, const char* filename)
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
void Control::send(QString file)
{
    //--------------s----------------
    std::cout <<"lll"<<file.toStdString()<<"lll"<<std::endl;
    boost::asio::io_service io;
    char csong[100];
    int length = file.toStdString().copy(csong,99);
    csong[length] = '\0';
    //--------------e----------------------
    fsender(io,"127.0.0.1",1347,csong);
}

QString Control::getSongName(QString songName)
{
    std::string temp = songName.toStdString();
    int j =0;
    j = temp.rfind("/");
    return QString::fromStdString(temp.substr(j+1));

    //    for(int i=temp.length()-1;i>=0;i--)
    //    {
    //        if(temp[i] == "/") {
    //            j = i;
    //            break;
    //        }
    //    }
    //    for(j++;j<temp.length();j++)
    //    {
    //        int a =0;
    //        songName[a] = temp[j];
    //        a++;
    //    }
}

QString Control::ID()
{
    return personalInfo-> m_ID;
}

void Control::setID(QString n)
{
    personalInfo-> m_ID = n;
    emit IDChanged();
}

QQmlListProperty<Song> Control::songlis()
{
    return QQmlListProperty<Song>(this, m_songlis);
}

void Control::setSonglis(QList<Song *> s)
{
    for(int i = 0;i!=m_songlis.length();i++)
        delete m_songlis[i];
    m_songlis = s;
    emit songlisChanged();
}

QQmlListProperty<Song> Control::downloa()
{
    return QQmlListProperty<Song>(this, personalInfo->m_downloa);
}

void Control::setDownloa(QList<Song *> d)
{
    personalInfo->m_downloa = d;
    emit downloaChanged();
}

QQmlListProperty<Song> Control::searc()
{
    return QQmlListProperty<Song>(this, m_searc);
}

void Control::setSearc(QList<Song *> s)
{
    m_searc = s;
    emit searcChanged();
}

QQmlListProperty<Song> Control::ilik()
{
    return QQmlListProperty<Song>(this, personalInfo->m_ilik);
}

void Control::setIlik(QList<Song *> i)
{
    personalInfo->m_ilik = i;
    emit ilikChanged();
}

QQmlListProperty<Song> Control::playlist()
{
    return QQmlListProperty<Song>(this, m_playlist);
}

void Control::setPlaylist(QList<Song *> l)
{
    m_playlist = l;
    emit playlistChange();
}

QList<QString> Control::songSheet()
{
    return personalInfo->m_songSheet;
}

QQmlListProperty<Song> Control::tempSheet()
{
    return QQmlListProperty<Song>(this, personalInfo->m_tempSheet);
}

QQmlListProperty<Treat> Control::treat()
{
    return QQmlListProperty<Treat>(this, m_treat);
}

Control::~Control()
{

    delete personalInfo;
    for(int i = 0;i!=m_songlis.length();i++)
        delete m_songlis[i];
    for(int i = 0;i!=m_searc.length();i++)
        delete m_searc[i];
    for(int i = 0;i!=m_playlist.length();i++)
        delete m_playlist[i];
}



