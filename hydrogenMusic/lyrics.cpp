#include "lyrics.h"
#include <iostream>
#include <fstream>
#include <QString>
#include <QDebug>

void Lyric::readLyric()
{
    m_header <<"ti:"<<"ar:"<<"al:"<<"by:";

    m_lineNum=0;
    std::ifstream fin("../hydrogenMusic/a");

    std::string str;
    getline(fin, str);
    while(fin)
    {
        if(str != "")
        {
            analysisOneLine(str);
        }
        getline(fin, str);
    }

    fin.close();
}

void Lyric::analysisOneLine(std::string str)
{
    if(str[0] != '[')
    {
        return;  //歌词文件格式不正规
    }

    //歌词说明 ti:歌曲名称 ar:演唱者 al: by: 制作单位
    if(getLyricHeader(str)) return;

    int m, n, p = 0;
    std::string timeTemp[MAX_LYRCE_REPEAT_NUM];//歌词重复
    m = str.find_first_of('[');
    n = str.find_first_of(']');
    while(m >= 0 && m <= str.length() && n >= 0 && n <= str.length() && str != "")
    {
        timeTemp[p] = str.substr(m + 1, n - 1);
        p++;
        str = str.substr(n + 1, str.length());
        m = str.find_first_of('[');
        n = str.find_first_of(']');
    }

    QString contentTemp = QString::fromStdString(str);

    for(int i = 0; i < p; i++)
    {

        m_startTime.append(changeStringToInt(timeTemp[i]));

//        if(timeTemp[i + 1] != "") //一行连续的...
//        {
//            lyric[lineNum].endTime = timeTemp[i + 1];
//            //cout << timeTemp[i] << endl;
//        }

        if(m_lineNum - 1 >= 0 && i == 0) { //设置上一个的endTime
            m_endTime.append(m_startTime[m_lineNum]);
        }
        else
            m_endTime.append(changeStringToInt("00:00.00"));
        m_lyricContent.append(contentTemp);
        m_lineNum++;
    }

}


bool Lyric::getLyricHeader(std::string str)
{
    for(int i = 0; i < 4; i++)
    {

        if(m_header[i] == QString::fromStdString(str.substr(1, 3)))
        {
            m_Lheader.append(QString::fromStdString(str));
            return true;
        }
    }
    return false;
}



int Lyric::changeStringToInt(std::string str_time)
{
    int time, min, sec, msc = 0; //分钟,秒,毫秒 转换成毫秒
    min = atof(const_cast<const char *>(str_time.substr(0, 2).c_str()));
    sec = atof(const_cast<const char *>(str_time.substr(3, 2).c_str()));
    if(str_time.length() > 5)
        msc = atof(const_cast<const char *>(str_time.substr(6, 2).c_str()));
    time = min * 60 * 1000 + sec * 1000 + msc;
    return time;
}


QList<QString> Lyric::header() const
{
    return m_header;
}

int Lyric::lineNum() const
{
    return m_lineNum;
}

QList<QString> Lyric::lheader() const
{
    return m_Lheader;
}

void Lyric::setlheader(QList<QString> &l)
{
    m_Lheader = l;
    emit lheaderChanged();
}

QList<QString> Lyric::lyricContent() const
{
    return m_lyricContent;
}

void Lyric::setlyricContent(QList<QString> &lc)
{
    m_lyricContent = lc;
    emit lyricContentChanged();
}

QList<int> Lyric::endTime() const
{
    return m_endTime;
}

QList<int> Lyric::startTime() const
{
    return m_startTime;
}

void Lyric::setstartTime(QList<int> &s)
{
    m_startTime = s;
    emit startTimeChanged();
}

