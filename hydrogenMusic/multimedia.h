#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <QObject>
#include <QQmlListProperty>
#include <string>
#include <QVariant>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <vector>
#include <string>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

extern "C"{
#include <string.h>
}

class Multimediaa:public QObject
{
    Q_OBJECT
public:
    Multimediaa() {}
    int init_multimedia(char *url);
    std::vector<std::string> get_song_infos(char *url);
    //这个函数是返回mp3流里的信息，按照 人名-歌名-专辑名-专辑艺术家名 返回
    //如果其中有一个没有,vector会返回空串

public slots:
    int init_multimedia2();
    void play_multimedia();
    void pause_mulitimedia();
    void stop_mulitimedia();
    int get_all_schedule();
    int get_current_schedule();
    void set_url(QString url);

    //gei m_url  fuzhi
private:
    std::string m_playerState = "stop";    //播放器的状态，分别是播放、暂停、停止
//    char * m_url = "\0";
    char m_url[100] = "";


//private:
//    int m_pause = 0;
};

int play_mp3(QString url2);
void pause_mp3(int &pause);

#endif // MULTIMEDIA_H
