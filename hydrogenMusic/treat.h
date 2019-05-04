#ifndef TREAT_H
#define TREAT_H
#include <QString>
#include <QObject>

class Treat :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ID READ id CONSTANT)
    Q_PROPERTY(QString textt READ text CONSTANT)
    Q_PROPERTY(QList<QString> songg READ song CONSTANT)
    Q_PROPERTY(QString timee READ time CONSTANT)
public:
    Treat();
    Treat(QString id,QString text,QList<QString> song,QString time):
        m_id(id),
        m_text(text),
        m_song(song),
        m_time(time){}

    QString id();
    QString text();
    QList<QString> song();
    QString time();
private:
    QString m_id;
    QString m_text;
    QList<QString> m_song;
    QString m_time;
};

#endif // TREAT_H
