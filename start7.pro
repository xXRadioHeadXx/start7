TEMPLATE = subdirs serialport

SUBDIRS += \
#    m_cfg \
    m_db \
    m_server

CONFIG += c++14 -std=gnu++14 -std=c++14

#include(src/src.pri)
