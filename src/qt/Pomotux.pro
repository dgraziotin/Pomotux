# -------------------------------------------------
# Project created by QtCreator 2009-04-29T11:13:00
# -------------------------------------------------
TARGET = Pomotux
TEMPLATE = app
SOURCES += gui_activityinventorysheet.cpp \
    insertnewactivity.cpp \
    main.cpp \
    modifyactivity.cpp \
    pomodoro.cpp \
    gui_todotodaysheet.cpp \
    ../activity.cpp \
    ../activityinventorysheet.cpp \
    ../pomotuxdatabase.cpp \
    ../todotodaysheet.cpp \
    pomotuxexception.cpp \
    preferencesdialog.cpp \
    aboutwindow.cpp
HEADERS += gui_activityinventorysheet.hpp \
    insertnewactivity.hpp \
    modifyactivity.hpp \
    pomodoro.hpp \
    gui_todotodaysheet.hpp \
    ../pomotuxdatabase.hpp \
    pomotuxexception.hpp \
    preferencesdialog.hpp \
    aboutwindow.h
FORMS += gui_activityinventorysheet.ui \
    insertnewactivity.ui \
    modifyactivity.ui \
    gui_todotodaysheet.ui \
    preferencesdialog.ui \
    aboutwindow.ui
OTHER_FILES += Pomotux.pro.user \
    pomodoro.pro \
    Pomotux.pro.user
LIBS += -llitesql \
    -lsqlite3 \
    -lpthread
