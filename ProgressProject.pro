#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T02:05:38
#
#-------------------------------------------------

QT       += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgressProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addhabit.cpp \
    Habit.cpp \
    HabitOp.cpp \
    viewhabit.cpp \
    edithabit.cpp \
    statistics.cpp \
    LogOp.cpp \
    ScoreCalc.cpp \
    qcustomplot.cpp \
    lav.cpp \
    goal.cpp \
    filecontrol.cpp \
    Cons.cpp \
    operations.cpp

HEADERS  += mainwindow.h \
    addhabit.h \
    Habit.h \
    HabitOp.h \
    viewhabit.h \
    edithabit.h \
    statistics.h \
    LogOp.h \
    ScoreCalc.h \
    qcustomplot.h \
    lav.h \
    goal.h \
    filecontrol.h \
    Cons.h \
    operations.h

FORMS    += mainwindow.ui \
    addhabit.ui \
    viewhabit.ui \
    edithabit.ui \
    statistics.ui

RESOURCES += \
    res.qrc
