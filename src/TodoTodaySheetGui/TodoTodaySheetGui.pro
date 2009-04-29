# -------------------------------------------------
# Project created by QtCreator 2009-04-27T10:22:46
# -------------------------------------------------
TARGET = TodoTodaySheetGui
TEMPLATE = app
SOURCES += main.cpp \
    todotodaysheetgui.cpp \
    ../pomotuxdatabase.cpp \
    ../activity.cpp \
    ../activityinventorysheet.cpp \
    ../todotodaysheet.cpp \
    ../gui/pomodoro/pomodoro.cpp \
    ../ActivityInventorySheetGui/modifyanactivity.cpp \
    ../ActivityInventorySheetGui/insertnewactivity.cpp \
    ../ActivityInventorySheetGui/guiactivityinventorysheet.cpp \
    mainwindow.cpp
HEADERS += todotodaysheetgui.h \
    ../pomotuxdatabase.hpp \
    ui_todotodaysheetgui.h \
    ../gui/pomodoro/pomodoro.hpp \
    ../ActivityInventorySheetGui/insertnewactivity.h \
    ../ActivityInventorySheetGui/guiactivityinventorysheet.h \
    mainwindow.h
FORMS += todotodaysheetgui.ui \
    ../ActivityInventorySheetGui/modifyanactivity.ui \
    ../ActivityInventorySheetGui/insertnewactivity.ui \
    ../ActivityInventorySheetGui/guiactivityinventorysheet.ui \
    mainwindow.ui
LIBS += -llitesql
