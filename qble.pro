QT += core
QT += gui
QT += widgets
QT += concurrent
QT += network
QT += serialbus
QT += serialport
QT += bluetooth
QT += dbus
QT += xml

###
TEMPLATE = app

###
CONFIG += c++11
CONFIG += sdk_no_version_check
CONFIG += nostrip
CONFIG += debug
#CONFIG += lrelease
CONFIG += embed_translations
CONFIG += create_prl

linux|mac:{
	QMAKE_CXXFLAGS +=-g -Wno-missing-field-initializers -Wno-deprecated-declarations
}

mac:{
	## Mac OSX info.plist file with bluetooth keys
	MacBundleFiles.files = $$PWD/info.plist
	MacBundleFiles.path	= Contents
	QMAKE_BUNDLE_DATA += MacBundleFiles
	QMAKE_CFLAGS += -mmacosx-version-min=12.0
	QMAKE_CXXFLAGS += -mmacosx-version-min=12.0
}

HEADERS += \
    $$PWD/adaptermodel.h \
    $$PWD/qbledevice.h \
    $$PWD/qbleservice.h \
    $$PWD/qblecharacteristic.h \
    $$PWD/bluezadapter.h \
    qblewindow.h

SOURCES += \
    $$PWD/adaptermodel.cpp \
    $$PWD/qbledevice.cpp \
    $$PWD/qbleservice.cpp \
    $$PWD/qblecharacteristic.cpp \
    $$PWD/bluezadapter.cpp \
    main.cpp \
    qblewindow.cpp

DISTFILES += \
	info.plist \
	qble_en_US.ts

RESOURCES += \
	resources.qrc

FORMS += \
	qblewindow.ui

