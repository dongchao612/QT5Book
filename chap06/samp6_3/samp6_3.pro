QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qformdoc.cpp \
    qformtable.cpp \
    qwdialogheaders.cpp \
    qwdialogsize.cpp \
    qwmainwindow.cpp

HEADERS += \
    qformdoc.h \
    qformtable.h \
    qwdialogheaders.h \
    qwdialogsize.h \
    qwmainwindow.h

FORMS += \
    qformdoc.ui \
    qformtable.ui \
    qwdialogheaders.ui \
    qwdialogsize.ui \
    qwmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
