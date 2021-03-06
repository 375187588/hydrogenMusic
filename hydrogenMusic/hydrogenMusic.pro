# allows to add DEPLOYMENTFOLDERS and links to the V-Play library and QtCreator auto-completion
CONFIG += v-play

qmlFolder.source = qml
DEPLOYMENTFOLDERS += qmlFolder # comment for publishing

assetsFolder.source = assets
DEPLOYMENTFOLDERS += assetsFolder

# Add more folders to ship with the application here

RESOURCES += #    resources.qrc # uncomment for publishing

# NOTE: for PUBLISHING, perform the following steps:
# 1. comment the DEPLOYMENTFOLDERS += qmlFolder line above, to avoid shipping your qml files with the application (instead they get compiled to the app binary)
# 2. uncomment the resources.qrc file inclusion and add any qml subfolders to the .qrc file; this compiles your qml files and js files to the app binary and protects your source code
# 3. change the setMainQmlFile() call in main.cpp to the one starting with "qrc:/" - this loads the qml files from the resources
# for more details see the "Deployment Guides" in the V-Play Documentation

# during development, use the qmlFolder deployment because you then get shorter compilation times (the qml files do not need to be compiled to the binary but are just copied)
# also, for quickest deployment on Desktop disable the "Shadow Build" option in Projects/Builds - you can then select "Run Without Deployment" from the Build menu in Qt Creator if you only changed QML files; this speeds up application start, because your app is not copied & re-compiled but just re-interpreted


# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    lyrics.cpp \
    client.cpp \
    multimedia.cpp \
    personalinfo.cpp \
    song.cpp \
    control.cpp \
    treat.cpp \
    simpleplayer.cpp

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    OTHER_FILES += android/AndroidManifest.xml       android/build.gradle
}

ios {
    QMAKE_INFO_PLIST = ios/Project-Info.plist
    OTHER_FILES += $$QMAKE_INFO_PLIST
    
}

# set application icons for win and macx
win32 {
    RC_FILE += win/app_icon.rc
}
macx {
    ICON = macx/app_icon.icns
}

HEADERS += \
    lyrics.h \
    client.h \
    myerror.h \
    multimedia.h \
    file_info.h \
    receiver.h \
    personalinfo.h \
    song.h \
    control.h \
    treat.h \
    simpleplayer.h

QMAKE_LFLAGS += -lboost_system -lpthread -lboost_thread -lavcodec -lavformat -lswresample -lavutil -lSDL

DISTFILES += \
    qml/myscript.js \
    qml/Lyrics.qml \
    qml/SongInterface.qml \
    qml/SongList.qml \
    qml/Upload.qml \
    qml/Searchfor.qml \
    qml/Mainbar.qml \
    qml/Mine.qml \
    qml/Playlist.qml \
    qml/MusicCycle.qml \
    qml/Advertisement.qml \
    qml/OrdinarySearchfor.qml \
    qml/treat.qml \
    qml/songsheet.qml \
    qml/Songshow.qml
#-------xiaoyao------s----

LIBS       += -L/usr/local/lib64 -lVLCQtCore -lVLCQtWidgets
#LIBS       += -L/usr/local/qml -lVLCQt
INCLUDEPATH += /usr/local/include

#-------xiaoyao------e-------
