# -------------------------------------------------
# Project created by QtCreator 2009-04-27T09:50:43
# -------------------------------------------------
QT += opengl \
    sql \
    svg \
    testlib
TARGET = ais
TEMPLATE = app
SOURCES += main.cpp \
    guiactivityinventorysheet.cpp \
    ../sep/src/pomotuxdatabase.cpp \
    ../sep/src/activity.cpp \
    ../sep/src/activityinventorysheet.cpp \
    ../sep/src/todotodaysheet.cpp \
    insertnewactivity.cpp \
    modifyanactivity.cpp
HEADERS += guiactivityinventorysheet.h \
    ../sep/src/pomotuxdatabase.hpp \
    insertnewactivity.h \
    modifyanactivity.h
FORMS += guiactivityinventorysheet.ui \
    insertnewactivity.ui \
    modifyanactivity.ui
LIBS += -llitesql
