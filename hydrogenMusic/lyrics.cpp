#include "lyrics.h"
#include <iostream>
#include <fstream>
#include <QString>

void Lyric::readLyric()
{
    m_header <<"ti:"<<"ar:"<<"al:"<<"by:";

    m_Lheader << "aaa"<< "aaa"<< "aaa"<< "aaa";
    m_lineNum=0;
    std::ifstream fin("../hydrogenMusic/s");

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
    //printLyric();
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
        OneLineLyric l;

        l.m_startTime = QString::fromStdString(timeTemp[i]);
        m_lyric.append(&l);

//        if(timeTemp[i + 1] != "") //一行连续的...
//        {
//            lyric[lineNum].endTime = timeTemp[i + 1];
//            //cout << timeTemp[i] << endl;
//        }

        if(m_lineNum - 1 >= 0 && i == 0) //设置上一个的endTime
            m_lyric[m_lineNum - 1]->m_endTime = m_lyric[m_lineNum]->m_startTime;
        m_lyric[m_lineNum]->m_lineNum = m_lineNum;
        m_lyric[m_lineNum]->m_lyricContent = contentTemp;
        m_lineNum++;
    }

}


bool Lyric::getLyricHeader(std::string str)
{
    for(int i = 0; i < 4; i++)
    {

        if(m_header[i] == QString::fromStdString(str.substr(1, 3)))
        {
            m_Lheader.replace(i,QString::fromStdString(str));
            return true;
        }
    }
    return false;
}

//void Lyric::printLyric()
//{
//    cout << "歌曲信息:" << endl;
//    for(int i = 0; i < 4; i++)
//    {
//        cout << Lheader[i] << endl;
//    }

//    for(int i = 0; i < lineNum; i++)
//    {
//        if(lyric[i].startTime != "")
//        {
//            //            cout << "行    号:\t" << lyric[i].lineNum << endl;
//            //            cout << "开始时间:\t" << lyric[i].startTime << endl;
//            //            cout << "结束时间:\t" << lyric[i].endTime << endl;
//            cout /*<<" 歌词内容:\t"*/ << lyric[i].lyricContent << endl;
//            //cout << endl;
//        }
//    }
//}

int Lyric::changeStringToInt(std::string str_time)
{
    int time, min, sec, msc = 0; //分钟,秒,毫秒 转换成毫秒
    min = atof(const_cast<const char *>(str_time.substr(0, 2).c_str()));
    sec = atof(const_cast<const char *>(str_time.substr(3, 2).c_str()));
    if(str_time.length() > 5)
        msc = atof(const_cast<const char *>(str_time.substr(4, 2).c_str()));
    time = min * 60 * 100 + sec * 100 + msc;
    return time;
}

int Lyric::onelineLyricsCount(QQmlListProperty<OneLineLyric> *list)
{
    Lyric *g = qobject_cast<Lyric *>(list->object);
    if(g)
        return g->m_lyric.count();
    return 0;
}

OneLineLyric *Lyric::lyrics1(QQmlListProperty<OneLineLyric> *list, int index)
{
    Lyric *g = qobject_cast<Lyric *>(list->object);
    if(g)
        return g->m_lyric.at(index);
    return nullptr;
}



//void Lyric::setLyricNum(int num)
//{
//    m_lyricNum = m_lyric[num]->m_lyricContent;
//}

//QString Lyric::lyricNum()
//{
//    return m_lyricNum;
//}



QList<QString> Lyric::header() const
{
    return m_header;
}

int Lyric::lineNum() const
{
    return m_lineNum;
}

QList<QString> Lyric::Lheader() const
{
    return m_Lheader;
}

QQmlListProperty<OneLineLyric> Lyric::lyric()
{
    return QQmlListProperty<OneLineLyric>(this,this,&Lyric::onelineLyricsCount,&Lyric::lyrics1);
}
