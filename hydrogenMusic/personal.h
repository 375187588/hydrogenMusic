#ifndef PERSONAL_H
#define PERSONAL_H

#include <QString>
#include <QObject>
#include <iostream>
#include <boost/asio.hpp>

#include "client.h"
#include "multimedia.h"

//---------s----------
#include "file_info.h"
#include "receiver.h"
#include <string>
//---------e--------
using namespace boost::asio;

class Personal:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ID READ ID WRITE setID NOTIFY IDChanged)
    Q_PROPERTY(QList<QString> songlis READ songlis WRITE setSonglis NOTIFY songlisChanged)
    Q_PROPERTY(QList<QString> downloa READ downloa WRITE setDownloa NOTIFY downloaChanged)
    Q_PROPERTY(QList<QString> searc READ searc WRITE setSearc NOTIFY searcChanged)
    Q_PROPERTY(QList<QString> ilik READ ilik WRITE setIlik NOTIFY ilikChanged)
    Q_PROPERTY(QList<QString> playlist READ playlist WRITE setPlaylist NOTIFY playlistChanged)

public:
    Personal(QObject *parent = 0):QObject(parent), m_client(m_io){}
    Q_INVOKABLE void run();
    Q_INVOKABLE void sendMessage(QString m);
    Q_INVOKABLE QList<QString> returnInfo(QString url);
    Q_INVOKABLE bool isIlike(QString nameArID);
    QList<QString> detach(std::string ret);
    Q_INVOKABLE bool addToL(QList<QString> l);


    QString ID();
    void setID(QString n);
    QList<QString> songlis();
    void setSonglis(QList<QString> s);
    QList<QString> downloa();
    void setDownloa(QList<QString> d);
    QList<QString> searc();
    void setSearc(QList<QString> s);
    QList<QString> ilik();
    void setIlik(QList<QString> i);
    QList<QString> playlist(void);
    void setPlaylist(QList<QString> l);

signals:
    void IDChanged();
    void songlisChanged();
    void downloaChanged();
    void searcChanged();
    void ilikChanged();
    void playlistChanged();

    void songList();
    void downloadOk();
    void uploadOk();
    void searchOk();
    void registerOk();
    void registerFailed();
    void loginOk();
    void loginFailed();
    void ilikeOk();
    void ilikeShow();
    void downloadShow();
    void dislike();
private:
    std::string m_receiveMessage;
    QString m_sendMessage;
    io_service m_io;
    Client m_client;
    QString m_ID;
    QList<QString> m_songlis;
    QList<QString> m_downloa;
    QList<QString> m_searc;
    QList<QString> m_ilik;
    Multimediaa *media = new Multimediaa();
    QList<QString> m_playlist;

};
#endif // PERSONAL_H
