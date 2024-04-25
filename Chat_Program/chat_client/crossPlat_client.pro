QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addfriend.cpp \
    addgroup.cpp \
    chatlist.cpp \
    creategroup.cpp \
    groupchat.cpp \
    main.cpp \
    privatechat.cpp \
    recvthread.cpp \
    sendthread.cpp \
    widget.cpp

HEADERS += \
    addfriend.h \
    addgroup.h \
    chatlist.h \
    creategroup.h \
    groupchat.h \
    privatechat.h \
    recvthread.h \
    sendthread.h \
    widget.h

FORMS += \
    addfriend.ui \
    addgroup.ui \
    chatlist.ui \
    creategroup.ui \
    groupchat.ui \
    privatechat.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    btn_off.png \
    btn_on.png \
    close_hover.png \
    close_normal.png \
    login.jpg \
    max_hover.png \
    max_normal.png \
    min_hover.png \
    min_normal.png \
    normal_hover.png \
    normal_normal.png
