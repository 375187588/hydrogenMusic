TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH+= -I /usr/local/include/jrtplib3
LIBS += -L/usr/local/lib -ljrtp -lpthread -lboost_system -lboost_thread
SOURCES += main.cpp
DEFINES += _GLIBCXX_USE_CXX11_ABI=0
