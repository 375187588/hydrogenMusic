#ifndef SONG_H
#define SONG_H
#include <QString>
#include <QObject>
class Control;
class Song:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString songName READ songName CONSTANT)
    Q_PROPERTY(QString singer READ singer CONSTANT)
    Q_PROPERTY(QString album READ album CONSTANT)
    Q_PROPERTY(QString key READ key CONSTANT)
public:
    friend class Control;
    Song();
    Song(QString songName,QString singer,QString album,QString key):
        m_songName(songName),
        m_singer(singer),
        m_album(album),
        m_key(key){}

    QString songName();
    QString singer();
    QString album();
    QString key();

    QString m_songName;
    QString m_singer;
    QString m_album;
    QString m_key;
    int m_download;

};

#endif // SONG_H
