#-------------------------------------------------
#
# Project created by QtCreator 2014-08-23T11:00:11
# a
#-------------------------------------------------

QT       += core gui sql testlib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MealAdmin
TEMPLATE = app

LIBS += -lunittest++

SOURCES += main.cpp\
        mainwindow.cpp \
    dialogstructure.cpp \
    dialogsupplier.cpp \
    login.cpp \
    test.cpp \
    myclass.cpp \
    dialogadmin.cpp \
    restriction.cpp \
    dialogtest.cpp \
    dialogdishrestriction.cpp \
    dialoggetlistordereddishes.cpp \
    dialogudatedishes.cpp \
    dialoginsertdish.cpp

HEADERS  += mainwindow.h \
    connection.h \
    dialogstructure.h \
    dialogsupplier.h \
    login.h \
    myclass.h \
    dialogadmin.h \
    restriction.h \
    dialogtest.h \
    dialogdishrestriction.h \
    dialoggetlistordereddishes.h \
    dialogudatedishes.h \
    dialoginsertdish.h

FORMS    += mainwindow.ui \
    dialogstructure.ui \
    dialogsupplier.ui \
    login.ui \
    dialogadmin.ui \
    restriction.ui \
    dialogtest.ui \
    dialogdishrestriction.ui \
    dialoggetlistordereddishes.ui \
    dialogudatedishes.ui \
    dialoginsertdish.ui
