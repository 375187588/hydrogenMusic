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
public:
    SimplePlayer();
    //explicit SimplePlayer(QWidget *parent = 0);
    ~SimplePlayer();

//private slots:
    //void openLocal();
    Q_INVOKABLE void openUrl(QString add);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE float getpositon();
    Q_INVOKABLE float getlength();
    Q_INVOKABLE void setposition(int position);


private:

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;

};


#endif // SIMPLEPLAYER_H
