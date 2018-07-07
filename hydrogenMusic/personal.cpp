#include "personal.h"
#include <sstream>
#include <QJSValue>
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
    record >> head;
    if(head == "songListShow") {
        std::string ret;
        ret = m_receiveMessage.substr(head.length()+1);
        QList<QString> vec = detach(ret);
        m_songlis = detach(ret);
        emit songList(vec);
    }
    else if(head == "download") {
        std::cout << m_receiveMessage <<std::endl;
        std::string ret;
        record >> ret;
        if(ret == "ok") emit downloadOk();
    }else if(head == "upload") {
        std::string ret;
        record >> ret;
        if(ret == "ok") {
            emit uploadOk();
            sendMessage("songListShow");
        }
    }else if(head == "search") {
        std::string ret;
        ret = m_receiveMessage.substr(head.length()+1);
        QList<QString> vec = detach(ret);
        emit searchOk(vec);
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
            //            sendMessage("songListShow");
        }else{
            emit loginOk();
        }
    }
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
    while(rec >> temp1) {
        vec.append(QString::fromStdString(temp1));
        rec >> temp1;
        vec.append(QString::fromStdString(temp1));
        rec >> temp1;
        vec.append(QString::fromStdString(temp1));
        rec >> temp1;
        vec.append(QString::fromStdString(temp1));

        temp2.clear();
        while (rec >> temp1) {
            if(temp1 != "||" ) temp2 +=temp1;
            else break;
        }
        vec.append(QString::fromStdString(temp2));

        temp2.clear();
        while (rec >> temp1) {
            if(temp1 != "|||" ) temp2 +=temp1;
            else break;
        }
        vec.append(QString::fromStdString(temp2));
    }
    return vec;
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
