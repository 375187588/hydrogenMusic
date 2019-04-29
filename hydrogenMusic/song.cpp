#include "song.h"

Song::Song()
{

}

QString Song::songName()
{
    return m_songName;
}

QString Song::singer()
{
    return m_singer;
}

QString Song::album()
{
    return m_album;
}

QString Song::key()
{
    return m_key;
}
