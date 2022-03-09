QT += core 
CONFIG += c++14 -std=gnu++14 -std=c++14

INCLUDEPATH += $$PWD/

HEADERS += \
    $$PWD/ThreadPool.h \
#    $$PWD/ctpl.h \
    $$PWD/ctpl_stl.h

SOURCES += \
    $$PWD/ThreadPool.cpp
