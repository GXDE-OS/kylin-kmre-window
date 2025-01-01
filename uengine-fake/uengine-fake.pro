QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = uengine

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        commandoption.cpp \
        main.cpp

target.source  += $$TARGET
target.path = /usr/bin

INSTALLS += target

HEADERS += \
    commandoption.h
