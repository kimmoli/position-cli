# The name of your application
TARGET = position

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT -= gui
QT += positioning

target.path = /usr/bin/

DEFINES += "APPVERSION=\\\"$${SPECVERSION}\\\""

message($${DEFINES})

INSTALLS += target

SOURCES += src/position.cpp \
    src/geopos.cpp

OTHER_FILES += rpm/position.spec

HEADERS += \
    src/geopos.h


