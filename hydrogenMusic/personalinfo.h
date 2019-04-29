#ifndef PERSONALINFO_H
#define PERSONALINFO_H
#include <QString>
#include <QObject>

class Control;
class Song;
class PersonalInfo:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ID READ ID)
    Q_PROPERTY(QList<Song *> ilik READ ilik)
    Q_PROPERTY(QList<Song *> downloa READ downloa)
public:
    friend class Control;
    PersonalInfo();

    QString ID();
    QList<Song *> ilik();
    QList<Song *> downloa();

    QString m_ID;
    QList<Song *> m_ilik;
    QList<Song *> m_downloa;
};

#endif // PERSONALINFO_H
