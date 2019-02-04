#-------------------------------------------------
#
# Project created by QtCreator 2019-02-04T14:03:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pictureLibrary
TEMPLATE = app

win32-msvc* {
    contains(QT_ARCH, i386) {
        message("msvc 32-bit")
        INCLUDEPATH += C:/dev/3rdParty/exiv2
        LIBS += -LC:\dev\3rdParty\exiv2\lib -lexiv2.dll
    } else {
        message("msvc 64-bit")
        INCLUDEPATH += C:/dev/3rdParty/exiv2
        LIBS += -LC:\dev\3rdParty\exiv2\lib -lexiv2.dll
    }
}

win32-g++ {
    message("mingw")
    INCLUDEPATH += C:/dev/3rdParty/exiv2
    LIBS += -LC:\dev\3rdParty\exiv2\lib -lexiv2.dll
}

unix {
    message("*nix")
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        cmainwindow.cpp

HEADERS += \
        cmainwindow.h

FORMS += \
        cmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    LICENSE
