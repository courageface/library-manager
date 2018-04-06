#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T19:50:34
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += widgets
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = database_library_system
TEMPLATE = app


SOURCES += main.cpp\
    database.cpp \
    login.cpp \
    admin.cpp \
    operationwindow_1.cpp \
    operationwindow_2.cpp \
    operationwindow_3.cpp \
    librarydamin.cpp \
    reader.cpp \
    form.cpp

HEADERS  += \
    database.h \
    login.h \
    admin.h \
    operationwindow_1.h \
    operationwindow_2.h \
    operationwindow_3.h \
    librarydamin.h \
    reader.h \
    form.h

FORMS    += \
    login.ui \
    admin.ui \
    operationwindow_1.ui \
    operationwindow_2.ui \
    operationwindow_3.ui \
    librarydamin.ui \
    reader.ui \
    form.ui

RESOURCES +=
