QT       += core gui\
            multimedia\
            widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    armor.cpp \
    battle.cpp \
    beast.cpp \
    build.cpp \
    button.cpp \
    character.cpp \
    inventory.cpp \
    item.cpp \
    main.cpp \
    mainmenu.cpp \
    points.cpp \
    rest.cpp \
    start.cpp \
    store.cpp \
    weapon.cpp

HEADERS += \
    armor.h \
    battle.h \
    beast.h \
    build.h \
    button.h \
    character.h \
    inventory.h \
    item.h \
    mainmenu.h \
    points.h \
    rest.h \
    start.h \
    store.h \
    weapon.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    icon.qrc \
    sfx.qrc \
    soundtrack.qrc \
    sprite.qrc
