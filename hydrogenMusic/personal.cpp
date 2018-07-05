#include "personal.h"
#include <sstream>
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
        std::cout << head.length() <<std::endl;
        ret = m_receiveMessage.substr(head.length()+1);
        QList<QString> vec = detach(ret);
        emit songList(vec);
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
            sendMessage("songListShow");
        }
    }else if(head == "search") {
        std::string ret;
        ret = m_receiveMessage.substr(head.length()+1);
        QList<QString> vec = detach(ret);
        emit searchOk(vec);
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
    std::string head;
    bool ishead = true;
    std::string head1;
    while (rec >> head) {
        if(head != "|||" && !ishead) {
            head1 += head;
        }else if(head == "|||"){
            vec.append(QString::fromStdString(head1));
            head1.clear();
            ishead = true;
        }else if(ishead) {
            vec.append(QString::fromStdString(head));
            ishead = false;
        }
    }
    return vec;
}
