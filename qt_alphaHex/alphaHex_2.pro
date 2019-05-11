#-------------------------------------------------
#
# Project created by QtCreator 2019-04-03T15:33:01
#
#-------------------------------------------------

QT       += core gui
RC_ICONS = other/alphahex.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = alphaHex_2
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

CONFIG += c++11

SOURCES += \
    src/policy/ai_policy.cpp \
    src/policy/eval.cpp \
    src/policy/search.cpp \
    src/game/core.cpp \
    src/game/hexChess.cpp \
    src/gui/windows/consoleWindow.cpp \
    src/gui/windows/mainWindow.cpp \
    src/gui/widget/lcdWidget.cpp \
    src/gui/widget/logWidget.cpp \
    src/gui/widget/strhtml.cpp \
    src/gui/widget/viewWidget.cpp \
    src/main.cpp \
    src/policy/python.cpp

HEADERS += \
    inc/policy/eval.h \
    inc/policy/search.h \
    inc/game/core.h \
    inc/game/hexChess.h \
    inc/policy/aiPolicy.h \
    inc/gui/widget/lcdWidget.h \
    inc/gui/widget/logWidget.h \
    inc/gui/widget/viewWidget.h \
    inc/gui/window/consoleWindow.h \
    inc/gui/window/mainWindow.h \
    inc/gui/widget/strhtml.h
INCLUDEPATH += -I /home/reget/anaconda3/envs/keras/include/python3.6m \
                /home/reget/anaconda3/envs/keras/include
LIBS += -L/home/reget/anaconda3/envs/keras/lib/ -lpython3.6m

FORMS += \
    ui/consolewindow.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    other/alphahex.ico
