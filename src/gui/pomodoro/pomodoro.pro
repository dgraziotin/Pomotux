HEADERS = pomodoro.hpp
SOURCES = pomodoro.cpp \
    main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/pomodoro
sources.files = $$SOURCES \
    $$HEADERS \
    $$RESOURCES \
    $$FORMS \
    pomodoro.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/widgets/pomodoro
INSTALLS += target \
    sources
FORMS += 
