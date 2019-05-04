#ifndef PERSONALINFO_H
#define PERSONALINFO_H
#include <QString>
#include <QObject>
#include <QQmlListProperty>

class Control;
class Song;
class PersonalInfo:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ID READ ID)
    Q_PROPERTY(QQmlListProperty<Song> ilik READ ilik CONSTANT)
    Q_PROPERTY(QQmlListProperty<Song> downloa READ downloa CONSTANT)
    Q_PROPERTY(QQmlListProperty<Song> tempSheet READ tempSheet CONSTANT)
    Q_PROPERTY(QList<QString> songSheet READ songSheet CONSTANT)
public:
    friend class Control;
    PersonalInfo();

    QString ID();
    QQmlListProperty<Song> ilik();
    QQmlListProperty<Song> downloa();
    QList<QString> songSheet();
    QQmlListProperty<Song> tempSheet();

    QString m_ID;
    QList<Song *> m_ilik;
    QList<Song *> m_downloa;
    QList<Song *> m_tempSheet;
    QList<QString> m_songSheet;

};

#endif // PERSONALINFO_H
