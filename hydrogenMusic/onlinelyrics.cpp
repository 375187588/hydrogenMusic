#include "onelinelyric.h"
int OneLineLyric::lineNum() const
{
    return m_lineNum;
}

QString OneLineLyric::startTime() const
{
    return m_startTime;
}

QString OneLineLyric::endTime() const
{
    return m_endTime;
}

QString OneLineLyric::lyricContent() const
{
    return m_lyricContent;
}
