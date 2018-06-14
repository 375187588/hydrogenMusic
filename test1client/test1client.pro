TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += /root/include
LIBS += -L/root/lib -ljrtp
SOURCES += main.cpp
