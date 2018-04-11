#ifndef ONLINELYRIC_H
#define ONLINELYRIC_H
#include <QObject>
#include <string>
class OneLineLyric: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int lineNum READ lineNum)
    Q_PROPERTY(QString startTime READ startTime)
    Q_PROPERTY(QString endTime READ endTime)
    Q_PROPERTY(QString lyricContent READ lyricContent)
public:
    int lineNum() const;
    QString startTime() const;
    QString endTime() const;
    QString lyricContent() const;

    int m_lineNum;
    QString m_startTime;
    QString m_endTime;
    QString m_lyricContent;
};
#endif // ONLINELYRIC_H
