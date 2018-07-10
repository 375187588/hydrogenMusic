#include <QApplication>
#include <VPApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "lyrics.h"
#include "personal.h"
#include "multimedia.h"


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
    vplay.initialize(&engine);

    Personal personal;
//    personal.returnInfo("../hydrogenMusic/assets/music/Taylor Swift - Love Story.mp3");
    Multimediaa hyMediaPlayer;
    engine.rootContext()->setContextProperty("hyMediaPlayer",&hyMediaPlayer);
    engine.rootContext()->setContextProperty("personal",&personal);
    // use this during development
    // for PUBLISHING, use the entry point below
    vplay.setMainQmlFileName(QStringLiteral("qml/Main.qml"));

    // use this instead of the above call to avoid deployment of the qml files and compile them into the binary with qt's resource system qrc
    // this is the preferred deployment option for publishing games to the app stores, because then your qml files and js files are protected
    // to avoid deployment of your qml files and images, also comment the DEPLOYMENTFOLDERS command in the .pro file
    // also see the .pro file for more details
    // vplay.setMainQmlFileName(QStringLiteral("qrc:/qml/Main.qml"));

    engine.load(QUrl(vplay.mainQmlFileName()));

    return app.exec();
}
