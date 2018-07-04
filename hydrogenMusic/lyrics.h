#ifndef LYRICS_H
#define LYRICS_H
#include <QObject>
#include <QQmlListProperty>
#include <string>
#include <QVariant>
const int MAX_LYRCE_REPEAT_NUM = 10;


class Lyric:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> header READ header)
    Q_PROPERTY(int lineNum READ lineNum)
    Q_PROPERTY(QList<QString> lheader READ lheader WRITE setlheader NOTIFY lheaderChanged)

    Q_PROPERTY(QList<QString> lyricContent READ lyricContent WRITE setlyricContent NOTIFY lyricContentChanged)
    Q_PROPERTY(QList<int> endTime READ endTime)
    Q_PROPERTY(QList<int> startTime READ startTime WRITE setstartTime NOTIFY startTimeChanged)

public:
    explicit Lyric(QObject *parent = 0):QObject(parent)
    {readLyric();}

    QList<QString> header() const;
    int lineNum() const;
    QList<QString> lheader() const;
    void setlheader(QList<QString> &l);

    QList<QString> lyricContent() const;
    void setlyricContent(QList<QString> &lc);
    QList<int> endTime() const;
    QList<int> startTime() const;
    void setstartTime(QList<int> &s);

    Q_INVOKABLE void readLyric();
    void analysisOneLine(std::string str);
    bool getLyricHeader(std::string str);

    Q_INVOKABLE int changeStringToInt(std::string str_time);
signals:
    void lheaderChanged();
    void lyricContentChanged();
    void startTimeChanged();
private:

    QList<QString> m_header;
    int m_lineNum;
    QList<QString> m_Lheader;
    QList<QString> m_lyricContent;
    QList<int> m_endTime;
    QList<int> m_startTime;
};


#endif // LYRICS_H
