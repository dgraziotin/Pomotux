# -------------------------------------------------
# Project created by QtCreator 2009-04-29T11:13:00
# -------------------------------------------------
TARGET = Pomotux
TEMPLATE = app
SOURCES += gui_activityinventorysheet.cpp \
    insertnewactivity.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyactivity.cpp \
    pomodoro.cpp \
    gui_todotodaysheet.cpp \
    ../activity.cpp \
	../activityinventorysheet.cpp \
	../pomotuxdatabase.cpp \
	../todotodaysheet.cpp 
HEADERS += gui_activityinventorysheet.hpp \
    insertnewactivity.hpp \
    mainwindow.hpp \
    modifyactivity.hpp \
    pomodoro.hpp \
    gui_todotodaysheet.hpp \
	../pomotuxdatabase.hpp
FORMS += gui_activityinventorysheet.ui \
    insertnewactivity.ui \
    mainwindow.ui \
    modifyactivity.ui \
    gui_todotodaysheet.ui
OTHER_FILES += Pomotux.pro.user \
    pomodoro.pro \
    Pomotux.pro.user
LIBS += -llitesql
