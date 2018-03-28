QT += quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp src/HueAPI.cpp
HEADERS += include/HueAPI.hpp
INCLUDEPATH += include /usr/local/include
LIBS += -L/usr/local/lib -lhueplusplusshared

RESOURCES += qml.qrc

QML_IMPORT_PATH += qml

target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
