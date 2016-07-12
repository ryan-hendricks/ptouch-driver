TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ptouch_test.cpp \
    ptouch_driver.cpp \
    ptouch_printer.cpp

HEADERS += \
    main.h \
    ptouch_driver.h \
    ptouch_printer.h

unix|win32: LIBS += -lusb-1.0
