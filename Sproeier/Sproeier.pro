QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sproeier
TEMPLATE = app

SOURCES += \
    StateMachine.cpp \
    subsystems_SM.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    SM.h \
    MainWindow.h \
    AppInfo.h

FORMS +=
