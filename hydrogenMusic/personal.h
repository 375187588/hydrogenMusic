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
    Q_PROPERTY(QString ID READ ID WRITE setID NOTIFY IDChanged)
    Q_PROPERTY(QList<QString> songlis READ songlis WRITE setSonglis NOTIFY songlisChanged)
public:
    Personal(QObject *parent = 0):QObject(parent), m_client(m_io),m_ID("MM"){}
    Q_INVOKABLE void run();
    Q_INVOKABLE void sendMessage(QString m);
    QList<QString> detach(std::string ret);

    QString ID();
    void setID(QString n);
    QList<QString> songlis();
    void setSonglis(QList<QString> s);
signals:
    void IDChanged();
    void songlisChanged();

    void songList(QList<QString> vec);
    void downloadOk();
    void uploadOk();
    void searchOk(QList<QString> vec);
    void registerOk();
    void registerFailed();
    void loginOk();
    void loginFailed();
private:
    std::string m_receiveMessage;
    QString m_sendMessage;
    io_service m_io;
    Client m_client;
    QString m_ID;
    QList<QString> m_songlis;
};
#endif // PERSONAL_H
