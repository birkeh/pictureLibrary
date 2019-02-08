#-------------------------------------------------
#
# Project created by QtCreator 2019-02-04T14:03:51
#
#-------------------------------------------------

VERSION = 0.0.1.0
QMAKE_TARGET_COMPANY = WIN-DESIGN
QMAKE_TARGET_PRODUCT = pictureLibrary
QMAKE_TARGET_DESCRIPTION = pictureLibrary
QMAKE_TARGET_COPYRIGHT = (c) 2019 WIN-DESIGN

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pictureLibrary
TEMPLATE = app

win32-msvc* {
    contains(QT_ARCH, i386) {
        message("msvc 32-bit")
        INCLUDEPATH += C:/dev/3rdParty/exiv2/include
        LIBS += -LC:\dev\3rdParty\exiv2\lib -lexiv2.dll
    } else {
        message("msvc 64-bit")
        INCLUDEPATH += C:/dev/3rdParty/exiv2/include
        LIBS += -LC:\dev\3rdParty\exiv2\lib -lexiv2.dll
    }
}

win32-g++ {
    message("mingw")
    INCLUDEPATH += C:/dev/3rdParty/exiv2/include
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
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        cmainwindow.cpp \
    cexif.cpp \
    csplashscreen.cpp \
    common.cpp \
    cpicturelibrary.cpp \
    cpicture.cpp

HEADERS += \
        cmainwindow.h \
    cexif.h \
    csplashscreen.h \
    common.h \
    cpicturelibrary.h \
    cpicture.h

FORMS += \
        cmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    LICENSE \
    Doxyfile \
    qdarkstyle/rc/branch_closed-on.png \
    qdarkstyle/rc/branch_closed.png \
    qdarkstyle/rc/branch_open-on.png \
    qdarkstyle/rc/branch_open.png \
    qdarkstyle/rc/checkbox_checked.png \
    qdarkstyle/rc/checkbox_checked_disabled.png \
    qdarkstyle/rc/checkbox_checked_focus.png \
    qdarkstyle/rc/checkbox_indeterminate.png \
    qdarkstyle/rc/checkbox_indeterminate_disabled.png \
    qdarkstyle/rc/checkbox_indeterminate_focus.png \
    qdarkstyle/rc/checkbox_unchecked.png \
    qdarkstyle/rc/checkbox_unchecked_disabled.png \
    qdarkstyle/rc/checkbox_unchecked_focus.png \
    qdarkstyle/rc/close-hover.png \
    qdarkstyle/rc/close-pressed.png \
    qdarkstyle/rc/close.png \
    qdarkstyle/rc/down_arrow.png \
    qdarkstyle/rc/down_arrow_disabled.png \
    qdarkstyle/rc/Hmovetoolbar.png \
    qdarkstyle/rc/Hsepartoolbar.png \
    qdarkstyle/rc/left_arrow.png \
    qdarkstyle/rc/left_arrow_disabled.png \
    qdarkstyle/rc/radio_checked.png \
    qdarkstyle/rc/radio_checked_disabled.png \
    qdarkstyle/rc/radio_checked_focus.png \
    qdarkstyle/rc/radio_unchecked.png \
    qdarkstyle/rc/radio_unchecked_disabled.png \
    qdarkstyle/rc/radio_unchecked_focus.png \
    qdarkstyle/rc/right_arrow.png \
    qdarkstyle/rc/right_arrow_disabled.png \
    qdarkstyle/rc/sizegrip.png \
    qdarkstyle/rc/stylesheet-branch-end.png \
    qdarkstyle/rc/stylesheet-branch-more.png \
    qdarkstyle/rc/stylesheet-vline.png \
    qdarkstyle/rc/transparent.png \
    qdarkstyle/rc/undock.png \
    qdarkstyle/rc/up_arrow.png \
    qdarkstyle/rc/up_arrow_disabled.png \
    qdarkstyle/rc/Vmovetoolbar.png \
    qdarkstyle/rc/Vsepartoolbar.png \
    qdarkstyle/style.qss

RESOURCES += \
    qdarkstyle/style.qrc \
    picturelibrary.qrc
