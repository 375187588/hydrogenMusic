//----author:xiaoyao

#include <QFileDialog>
#include <QInputDialog>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include "simpleplayer.h"


SimplePlayer::SimplePlayer():_media(0)
{


    _instance = new VlcInstance(VlcCommon::args(), NULL);
    _player = new VlcMediaPlayer(_instance);
    connect(_player,SIGNAL(end()),this,SLOT(onEnd()));

}

SimplePlayer::~SimplePlayer()
{
    delete _player;
    delete _media;
    delete _instance;

}

QString SimplePlayer::nextSongAddr()
{
    return m_nextSongAddr;
}

void SimplePlayer::setNextSongAddr(QString addr)
{
    m_nextSongAddr = addr;
}

//void SimplePlayer::openLocal()
//{
//    QString file =
//            QFileDialog::getOpenFileName(this, tr("Open file"),
//                                         QDir::homePath(),
//                                         tr("Multimedia files(*)"));

//    if (file.isEmpty())
//        return;

//    _media = new VlcMedia(file, true, _instance);

//    _player->open(_media);
//}

void SimplePlayer::openUrl(QString add)
{
    //QString url = "rtsp://192.168.42.193/test.mp3";
    //QString url = ;
    QString url = add;



    if (url.isEmpty())
        return;

//    if(_media!=nullptr)
//        delete _media;
    _media = new VlcMedia(url, _instance);


    _player->open(_media);
}
void SimplePlayer::play()
{
    _player->play();
}

void SimplePlayer::pause()
{
    _player->pause();
}
float SimplePlayer::getpositon()
{
    return _player->time();
}
float SimplePlayer::getlength()
{
    return _player->length();
}
void SimplePlayer::setposition(int position)
{
    _player->setTime(position);
}
