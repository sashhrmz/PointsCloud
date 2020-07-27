QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++14

TEMPLATE = app
TARGET   = frameTransform

HEADERS  = \
    pointsCloud.h
SOURCES  = main.cpp \
    pointsCloud.cpp

include( ../examples.pri )

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
