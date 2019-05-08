#ifndef SIMPLEPLAYER_H
#define SIMPLEPLAYER_H
//-------author:xiaoyao-------
#include <QMainWindow>
#include <QObject>



class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;



class SimplePlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nextSongAddr READ nextSongAddr WRITE setNextSongAddr CONSTANT)
public:
    SimplePlayer();
    //explicit SimplePlayer(QWidget *parent = 0);
    ~SimplePlayer();
    QString nextSongAddr();
    void setNextSongAddr(QString addr);
//private slots:
    //void openLocal();
    Q_INVOKABLE void openUrl(QString add);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE float getpositon();
    Q_INVOKABLE float getlength();
    Q_INVOKABLE void setposition(int position);

    QString m_nextSongAddr;

signals:
    void currentSongEnd();
public slots:
    void onEnd(){
        emit currentSongEnd();
//        delete _media;
//        _media=nullptr;
//        this->openUrl("rtsp:://0.0.0.0/test.mp3");
        //qDebug("onEnd");
    }
private:

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;

};


#endif // SIMPLEPLAYER_H
