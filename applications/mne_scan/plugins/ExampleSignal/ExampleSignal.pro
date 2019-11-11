#-------------------------------------------------
#
# Project created by QtCreator 2019-11-09T10:40:11
#
#-------------------------------------------------

include(../../../../mne-cpp.pri)

QT       += core widgets

QT       -= gui

TARGET = ExampleSignal
TEMPLATE = lib

DEFINES += EXAMPLESIGNAL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        examplesignal.cpp

HEADERS += \
        examplesignal.h \
        examplesignal_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L$${MNE_LIBRARY_DIR}
CONFIG(debug,debug|release|) {
    LIBS += -lMNE$${MNE_LIB_VERSION}Utilsd \
            -lscMeasd \
            -lscDispd \
            -lscSharedd \
            -lMagCPPd
}
else {
    LIBS += -lMNE$${MNE_LIB_VERSION}Utils \
            -lscMeas \
            -lscDisp \
            -lscShared \
            -lMagCPP
}

DESTDIR = $${MNE_BINARY_DIR}/mne_scan_plugins

INCLUDEPATH += $${EIGEN_INCLUDE_DIR}
INCLUDEPATH += $${MNE_INCLUDE_DIR}
INCLUDEPATH += $${MNE_SCAN_INCLUDE_DIR}

# Put generated form headers into the origin --> cause other src is pointing at them
UI_DIR = $$PWD

unix: QMAKE_CXXFLAGS += -isystem $$EIGEN_INCLUDE_DIR

# suppress visibility warnings
unix: QMAKE_CXXFLAGS += -Wno-attributes

DISTFILES += \
    examplesignal.json
