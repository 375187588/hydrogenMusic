#ifndef PERSONAL_H
#define PERSONAL_H

#include <QString>
#include <QObject>
#include <iostream>
#include <boost/asio.hpp>

#include "client.h"

using namespace boost::asio;

class Personal:public QObject
{
    Q_OBJECT
public:
    Personal(QObject *parent = 0):QObject(parent), m_client(m_io){}
    Q_INVOKABLE void run();
    Q_INVOKABLE void sendMessage(QString m);
    QList<QString> detach(std::string ret);
signals:
    void songList(QList<QString> vec);
    void downloadOk();
    void uploadOk();
    void searchOk(QList<QString> vec);
private:
    std::string m_receiveMessage;
    QString m_sendMessage;
    io_service m_io;
    Client m_client;
};
#endif // PERSONAL_H
