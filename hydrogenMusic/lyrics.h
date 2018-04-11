#ifndef LYRICS_H
#define LYRICS_H
#include <QObject>
#include <QQmlListProperty>
#include <string>
#include "onelinelyric.h"
//const int MAX_LYRIC_LINE_NUM =200;
const int MAX_LYRCE_REPEAT_NUM = 10;


class Lyric:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> header READ header)
    Q_PROPERTY(int lineNum READ lineNum)
    Q_PROPERTY(QList<QString> Lheader READ Lheader)
    Q_PROPERTY(QQmlListProperty<OneLineLyric> lyric READ lyric)
    //Q_PROPERTY(QString lyricContent READ lyricContent)
public:
    explicit Lyric(QObject *parent = 0):QObject(parent)
    {readLyric();}

    QList<QString> header() const;
    int lineNum() const;
    QList<QString> Lheader() const;

    Q_INVOKABLE void readLyric();
    QQmlListProperty<OneLineLyric> lyric();
    void analysisOneLine(std::string str);
    bool getLyricHeader(std::string str);
    int onelineLyricsCount() const;
    OneLineLyric* lyrics1(int index) const;
    //void printLyric();
    Q_INVOKABLE int changeStringToInt(std::string str_time);
    //Q_INVOKABLE void setLyricNum(int num);
    //QString lyricNum();


private:
    static int onelineLyricsCount(QQmlListProperty<OneLineLyric>*list);
    static OneLineLyric* lyrics1(QQmlListProperty<OneLineLyric>*list, int index);
    QList<QString> m_header;
    int m_lineNum;
    QList<QString> m_Lheader;
    QList<OneLineLyric *> m_lyric;
    //QString m_lyricNum;
};


#endif // LYRICS_H
