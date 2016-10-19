TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += qt thread debug
CONFIG += c++14

LIBS += -L/path/boost/lib/ -lboost_thread -lboost_system -lboost_chrono

SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    stdfx.h \
    main.hpp
