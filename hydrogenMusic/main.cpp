#include <QApplication>
#include <VPApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "lyrics.h"
#include "control.h"
#include "multimedia.h"
#include "song.h"
#include "personalinfo.h"
//------------xiaoyao---s---------
//#include <QtCore/QCoreApplication>
//#include <QtWidgets/QApplication>
//#include <QQmlContext>
#include <VLCQtCore/Common.h>

#include "simpleplayer.h"

//------------xiaoyao-----e-----

void receive()
{
    asio::io_service io;
    Tcp_server receiver(io, 1345);
    io.run();
}

int main(int argc, char *argv[])
{
    //------------------s--------------
    std::cout << "s" << std::endl;
//    asio::io_service io;
//    Tcp_server receiver(io,1345);
//    boost::thread th(boost::bind(&Tcp_server::start_accept, &receiver));

//    io.run();
    boost::thread th(&receive);
    //th.join();
    std::cout << "e" << std::endl;
        //---------------e-------------

    QApplication app(argc, argv);
    VPApplication vplay;

    // Use platform-specific fonts instead of V-Play's default font
    vplay.setPreservePlatformFonts(true);

    QQmlApplicationEngine engine;
    Lyric lyric;
    engine.rootContext()->setContextProperty("qtLyric",&lyric);
    //------------xiaoyao---s---------
    SimplePlayer player;
    //player.openUrl();
    engine.rootContext()->setContextProperty("simplePlayer",&player);

    //------------xiaoyao-----e-----

    vplay.initialize(&engine);

    Control control;
    Multimediaa hyMediaPlayer;
    engine.rootContext()->setContextProperty("hyMediaPlayer",&hyMediaPlayer);
    engine.rootContext()->setContextProperty("control",&control);
    qmlRegisterType<PersonalInfo>("PersonalInfo",1,0,"PersonalInfo");
    qmlRegisterType<Song>("Song",1,0,"Song");
    // use this during development
    // for PUBLISHING, use the entry point below
    vplay.setMainQmlFileName(QStringLiteral("qml/Main.qml"));



    engine.load(QUrl(vplay.mainQmlFileName()));
    //----xiaoyao------s------
    QCoreApplication::setApplicationName("VLC-Qt Simple Player");
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
    VlcCommon::setPluginPath(app.applicationDirPath() + "/plugins");

    //-----xiaoyao-----e------------
    return app.exec();
}
