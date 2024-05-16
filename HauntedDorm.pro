QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HauntedDorm
TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbuildingform.cpp \
    bed.cpp \
    cage.cpp \
    door.cpp \
    floorcage.cpp \
    gameover.cpp \
    ghost.cpp \
    haunteddormgame.cpp \
    human.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    menu.cpp \
    room.cpp \
    settings.cpp \
    upgrateform.cpp

HEADERS += \
    addbuildingform.h \
    bed.h \
    cage.h \
    door.h \
    floorcage.h \
    gameover.h \
    ghost.h \
    haunteddormgame.h \
    human.h \
    mainwindow.h \
    map.h \
    menu.h \
    room.h \
    settings.h \
    upgrateform.h

FORMS += \
    addbuildingform.ui \
    gameover.ui \
    map.ui \
    menu.ui \
    settings.ui \
    upgrateform.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cache \
    images/icon.png \
    setting-style.qss

RESOURCES += \
    resourses.qrc
