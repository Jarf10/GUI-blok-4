#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T11:02:10
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMjarvin
TEMPLATE = app

SOURCES += \
    main.cpp\
    MainWindow.cpp \
    StateMachine.cpp \
    sm_settings.cpp \
    subsystems_sm.cpp \
    Led.cpp \
    Widgetwithbackground.cpp

HEADERS += \
    MainWindow.h \
    StateMachine.h \
    AppInfo.h \
    Led.h \
    Widgetwithbackground.h

FORMS +=

RESOURCES += \
    SMjarvin.qrc
