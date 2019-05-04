#include "personalinfo.h"

PersonalInfo::PersonalInfo()
{

}

QString PersonalInfo::ID()
{
    return m_ID;
}

QQmlListProperty<Song> PersonalInfo::ilik()
{
    return QQmlListProperty<Song>(this,m_ilik);
}

QQmlListProperty<Song> PersonalInfo::downloa()
{
    return QQmlListProperty<Song>(this,m_downloa);
}

QList<QString> PersonalInfo::songSheet()
{
    return m_songSheet;
}

QQmlListProperty<Song> PersonalInfo::tempSheet()
{
    QQmlListProperty<Song>(this,m_tempSheet);
}
