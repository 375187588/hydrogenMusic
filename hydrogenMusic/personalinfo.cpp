#include "personalinfo.h"

PersonalInfo::PersonalInfo()
{

}

QString PersonalInfo::ID()
{
    return m_ID;
}

QList<Song *> PersonalInfo::ilik()
{
    return m_ilik;
}

QList<Song *> PersonalInfo::downloa()
{
    return m_downloa;
}
