QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bulletchat.cpp \
    main.cpp \
    mainwindow.cpp \
    option/barragesettings.cpp \
    option/initPage.cpp \
    option/option.cpp \
    option/shortcutkeyssettings.cpp \
    outlinedlabel.cpp \
    tray.cpp

HEADERS += \
    bulletchat.h \
    mainwindow.h \
    option/barragesettings.h \
    option/option.h \
    option/shortcutkeyssettings.h \
    outlinedlabel.h \
    tray.h

FORMS += \
    mainwindow.ui \
    option/option.ui

TRANSLATIONS += \
    DictionaryBarrage_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include("E:\environment\c++\qt Tripartite library\QHotkey-1.5.0\qhotkey.pri")

RESOURCES += \
    icon.qrc
