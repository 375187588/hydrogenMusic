#include "treat.h"

Treat::Treat()
{

}

QString Treat::id()
{
    return m_id;
}

QString Treat::text()
{
    return m_text;
}

QList<QString> Treat::song()
{
    return m_song;
}

QString Treat::time()
{
    return m_time;
}
