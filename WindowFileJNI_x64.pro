#-------------------------------------------------
#
# Project created by QtCreator 2018-01-31T20:04:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WindowFileJNI_x64
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myreadfile.cpp \
    actionswithvectors.cpp \
    myjavainterface.cpp \
    vertex.cpp \
    myclustering.cpp

HEADERS += \
        mainwindow.h \
    myreadfile.h \
    actionswithvectors.h \
    myjavainterface.h \
    vertex.h \
    myclustering.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += \
    "D:/boost_1_66_0/boost_msvc_141_static/include/boost-1_66" \
    "$$(JAVA_HOME)/include" \
    "$$(JAVA_HOME)/include/win32" \
    "D:/ONPU/Diplom/dlib-19.9"
LIBS += \
    -L"D:/boost_1_66_0/boost_msvc_141_static/lib" -llibboost_iostreams-vc141-mt-x64-1_66 \
    -L"$$(JAVA_HOME)/lib" -ljvm
