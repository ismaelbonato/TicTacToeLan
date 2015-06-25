#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T23:40:50
#
#-------------------------------------------------
QT       += core gui
QT       += network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projetofinal
TEMPLATE = app

SOURCES += main.cpp\
        interface.cpp \
    jogo_da_velha.cpp \
    server.cpp \
    peermanager.cpp \
    connection.cpp \
    client.cpp \
    table.cpp

HEADERS  += interface.h \
    jogo_da_velha.h \
    server.h \
    peermanager.h \
    connection.h \
    client.h \
    table.h

FORMS    += interface.ui \
    table.ui \
    load.ui

RESOURCES += \
    res.qrc
