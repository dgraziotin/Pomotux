# -------------------------------------------------
# Project created by QtCreator 2009-04-29T11:13:00
# -------------------------------------------------

TEMPLATE = app

OBJECTS_DIR = ./build/obj
MOC_DIR = ./build/moc
UI_DIR = ./build/ui
TARGET = ./bin/pomotux
target.path = /usr/bin


SOURCES += src/qt/gui_activityinventorysheet.cpp \
    src/qt/insertnewactivity.cpp \
    src/qt/main.cpp \
    src/qt/modifyactivity.cpp \
    src/qt/pomodoro.cpp \
    src/qt/gui_todotodaysheet.cpp \
    src/activity.cpp \
    src/activityinventorysheet.cpp \
    src/pomotuxdatabase.cpp \
    src/todotodaysheet.cpp \
    src/qt/pomotuxexception.cpp \
    src/qt/preferencesdialog.cpp \
    src/qt/aboutwindow.cpp
HEADERS += src/qt/gui_activityinventorysheet.hpp \
    src/qt/insertnewactivity.hpp \
    src/qt/modifyactivity.hpp \
    src/qt/pomodoro.hpp \
    src/qt/gui_todotodaysheet.hpp \
    src/pomotuxdatabase.hpp \
    src/qt/pomotuxexception.hpp \
    src/qt/preferencesdialog.hpp \
    src/qt/aboutwindow.h
FORMS += src/qt/gui_activityinventorysheet.ui \
    src/qt/insertnewactivity.ui \
    src/qt/modifyactivity.ui \
    src/qt/gui_todotodaysheet.ui \
    src/qt/preferencesdialog.ui \
    src/qt/aboutwindow.ui
OTHER_FILES += src/qt/Pomotux.pro.user \
    pomodoro.pro \


LIBS +=-llitesql \
    -lsqlite3 \
    -lpthread

INSTALLS = target
