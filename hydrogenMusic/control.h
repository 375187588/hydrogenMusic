#ifndef CONTROL_H
#define CONTROL_H

#include <QString>
#include <QObject>
#include <boost/asio.hpp>

#include "client.h"
#include "multimedia.h"

//---------s----------
#include "file_info.h"
#include "receiver.h"
#include <string>
//---------e--------
//-----------s----------

#include <cstdio>
#include <cstring>
#include <boost/shared_ptr.hpp>
#include <QQmlListProperty>

using namespace boost::asio;

class PersonalInfo;
class Song;
class Treat;
class Control:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ID READ ID WRITE setID NOTIFY IDChanged)
    Q_PROPERTY(QQmlListProperty<Song> songlis READ songlis CONSTANT)
    Q_PROPERTY(QQmlListProperty<Song> downloa READ downloa CONSTANT)
    Q_PROPERTY(QQmlListProperty<Song> searc READ searc CONSTANT)
    Q_PROPERTY(QQmlListProperty<Song> ilik READ ilik CONSTANT)
    Q_PROPERTY(QQmlListProperty<Song> playlist READ playlist CONSTANT)
    Q_PROPERTY(QList<QString> songSheet READ songSheet CONSTANT)
    Q_PROPERTY(QQmlListProperty<Song> tempSheet READ tempSheet CONSTANT)
    Q_PROPERTY(QQmlListProperty<Treat> treat READ treat CONSTANT)

public:
    Control(QObject *parent = 0):QObject(parent), m_client(m_io){}
    Q_INVOKABLE void run();
    Q_INVOKABLE void sendMessage(QString m);
    Q_INVOKABLE QList<QString> returnInfo(QString url);
    Q_INVOKABLE bool isIlike(QString nameAr);
    Q_INVOKABLE bool addToL(QString songName, QString singer, QString album, QString key);
    Q_INVOKABLE void deleteInPlaylist(int index);
    Q_INVOKABLE void upList(int index);
    Q_INVOKABLE QList<QString> nextSong(int model,int index);
    Q_INVOKABLE int currentSong(QString nameArID);
    Q_INVOKABLE void send(QString file);
    Q_INVOKABLE QString getSongName(QString songName); //get name from address of the song.
    QList<Song *> detach(std::string ret); //datach to song*
    QList<QString> detachToQstring(std::string ret);
    QList<Treat *> detachToTreat(std::string ret);
    QString timeTransf(QString time);

    QString ID();
    void setID(QString n); //have not use the func
    QQmlListProperty<Song> songlis();
    void setSonglis(QList<Song *> s);//have not use the func
    QQmlListProperty<Song> downloa();
    void setDownloa(QList<Song *> d);//have not use the func
    QQmlListProperty<Song> searc();
    void setSearc(QList<Song *> s);//have not use the func
    QQmlListProperty<Song> ilik();
    void setIlik(QList<Song *> i);//have not use the func
    QQmlListProperty<Song> playlist(void);
    void setPlaylist(QList<Song *> l);//have not use the func
    QList<QString> songSheet();
    QQmlListProperty<Song> tempSheet();
    QQmlListProperty<Treat> treat();
    ~Control();

signals:
    void IDChanged();
    void songlisChanged();
    void downloaChanged();
    void searcChanged();
    void ilikChanged();
    void playlistChanged();
    void playlistChange();

    void songList();
    void downloadOk();
    void uploadOk();
    void searchOk();
    void registerOk();
    void registerFailed();
    void loginOk();
    void touristsloginOk();
    void loginFailed();
    void ilikeOk();
    void ilikeShow();
    void downloadShow();
    void sheetListShow(QString sheetname);
    void songsheetAddSongOk(QString sheetname);
    void dislike();
    void songsheetAll();//已将所有歌单名存在personalInfo的m_songSheet中
    void songsheetAddOk(QString isOK);
    void sendtreatOk(QString isOK);
    void treatShow();
    void sheetInfo(QList<QString> info);
private:
    std::string m_receiveMessage;
    QString m_sendMessage;
    io_service m_io;
    Client m_client;
    PersonalInfo *personalInfo;
    QList<Song *> m_songlis;
    QList<Song *> m_searc;
    Multimediaa *media = new Multimediaa();
    QList<Song *> m_playlist;
    QList<Treat *>m_treat;

};
#endif // Control_H
