#include "personal.h"
#include <sstream>
#include <QJSValue>
#include <QUrl>
#include <vector>
void Personal::run()
{
    m_io.run();
    std::cout << "run" << std::endl;
}

void Personal::sendMessage(QString m)
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
        if(head1 == "ilike") {
            m_ilik = detach(ret);
            emit ilikeShow();
        }
        if(head1 == "download") {
            m_downloa = detach(ret);
            emit downloadShow();
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
            m_ID = QString::fromStdString(ret);
            emit loginOk();
        }
    }else if(head == "ilike") {
        std::string ret;
        record >> ret;
        if(ret == "ok") {
            sendMessage("songListShow ilike " + m_ID);
            emit ilikeOk();
        }
    }else if(head == "delete") {
        std::string ret;
        record >> ret;
        if(ret == "ilike") {
            record >> ret;
            if(ret == "ok") {
                sendMessage("songListShow ilike " + m_ID);
                emit dislike();
            }
        }else if(ret == "ilikes") {
            record >> ret;
            if(ret == "ok") sendMessage("songListShow ilike " + m_ID);
        }else if(ret == "download") {
            record >> ret;
            if(ret == "ok") sendMessage("songListShow download " + m_ID);
        }
    }else if(head == "tourists") {

        std::string ret;
        record >> ret;
        m_ID = QString::fromStdString(ret);
        emit touristsloginOk();
    }

}

QList<QString> Personal::returnInfo(QString url)
{
    printf("into personal::return n=info\n");
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



    printf("ch is %s\n", ch);
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
    std::cout << v[0]<<std::endl;
    QList<QString> l;
    l.append(QString::fromStdString(v[0]));
    l.append(QString::fromStdString(v[1]));
    l.append(QString::fromStdString(v[2]));
    std::cout <<l[0].toStdString()<<l[1].toStdString()<<l[2].toStdString() << std::endl;
    return l;

}

bool Personal::isIlike(QString nameAr)
{
    if(m_ilik.length() > 1) {
        for (int i = 0;i<m_ilik.length()/4;i++) {
            if(m_ilik[4*i + 3] == nameAr) {
                return true;
            }
        }
    }
    return false;
}

QList<QString> Personal::detach(std::string ret)
{
    QList<QString> vec;
    if(ret.empty()) {
        ret = "******";
        vec.append(QString::fromStdString(ret));
        return vec;
    }
    std::istringstream rec(ret);
    std::string temp1;
    std::string temp2;
    int t = 1;

    while(rec >> temp1) {
        if(temp1 != "||" && temp1 != "|||" ) {
            temp2 +=temp1;
            temp2 +=" ";
        }else {
            if(!temp2.empty()) {
                if(t%4 == 0) temp2 = temp2.substr(0,temp2.length()-1);
                vec.append(QString::fromStdString(temp2));
                t++;
                temp2.clear();
            }
        }
    }
    return vec;
}

bool Personal::addToL(QList<QString> l)
{
    if(m_playlist.length()>1) {
        for(int i=0;i<m_playlist.length()/4;i++) {
            if(m_playlist[4*i + 3] == l[3]) return false;
        }
    }
    for(int j=0;j<4;j++) {
        m_playlist.push_back(l[j]);
    }
    return true;


}

void Personal::deleteInPlaylist(int index)
{
    for(int j = index;j!=m_playlist.length()/4-1;j++) {
        if(j!=m_playlist.length()/4-1) {
            for(int i=0;i<4;i++) {
                m_playlist[4*j+ i] = m_playlist[4*(j+1)+ i];
            }
        }
    }

    for(int i=0;i<4;i++) {
        m_playlist.pop_back();
    }
    emit playlistChange();
}

void Personal::upList(int index)
{
    QList<QString> temp;
    for(int i = 0;i<4;i++) {
        temp.append(m_playlist[4*index +i]);
    }

    for(int j = index;j!=-1;j--) {
        if(j!=0) {
            for(int i=0;i<4;i++) {
                m_playlist[4*j+ i] = m_playlist[4*(j-1)+ i];
            }
        }else{
            for(int i=0;i<4;i++) {
                m_playlist[4*j+ i] = temp[i];
            }
        }
    }
    emit playlistChange();

}

int Personal::currentSong(QString nameArID)
{
    if(m_playlist.length() > 1) {
        for (int i = 0;i<m_playlist.length()/4;i++) {
            QString temp = m_playlist[4*i + 3] + " - " + m_ID;
            if(temp == nameArID) {
                return i;
            }
        }
    }else
        return 0;
}

QString Personal::ID()
{
    return m_ID;
}

void Personal::setID(QString n)
{
    m_ID = n;
    emit IDChanged();
}

QList<QString> Personal::songlis()
{
    return m_songlis;
}

void Personal::setSonglis(QList<QString> s)
{
    m_songlis = s;
    emit songlisChanged();
}

QList<QString> Personal::downloa()
{
    return m_downloa;
}

void Personal::setDownloa(QList<QString> d)
{
    m_downloa = d;
    emit downloaChanged();
}

QList<QString> Personal::searc()
{
    return m_searc;
}

void Personal::setSearc(QList<QString> s)
{
    m_searc = s;
    emit searcChanged();
}

QList<QString> Personal::ilik()
{
    return m_ilik;
}

void Personal::setIlik(QList<QString> i)
{
    m_ilik = i;
    emit ilikChanged();
}

QList<QString> Personal::playlist()
{
    return m_playlist;
}

void Personal::setPlaylist(QList<QString> l)
{
    m_playlist = l;
    emit playlistChange();
}


