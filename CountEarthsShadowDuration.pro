#-------------------------------------------------
#
# Project created by QtCreator 2023-05-29T10:06:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CountEarthsShadowDuration
TEMPLATE = app


SOURCES += main.cpp\
        chooseaction.cpp \
    shadowdurationoneday.cpp \
    onedaygso.cpp \
    shadowdurationyear.cpp \
    qcustomplot.cpp \
    graphicyeargso.cpp \
    durationperhour.cpp \
    graphicperhour.cpp \
    customshadowdurationoneday.cpp \
    onedaycustomorbit.cpp

HEADERS  += chooseaction.h \
    shadowdurationoneday.h \
    onedaygso.h \
    shadowdurationyear.h \
    qcustomplot.h \
    graphicyeargso.h \
    durationperhour.h \
    graphicperhour.h \
    customshadowdurationoneday.h \
    onedaycustomorbit.h

FORMS    += chooseaction.ui \
    shadowdurationoneday.ui \
    shadowdurationyear.ui \
    graphicyeargso.ui \
    durationperhour.ui \
    graphicperhour.ui \
    customshadowdurationoneday.ui
