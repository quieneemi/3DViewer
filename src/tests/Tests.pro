QT -= gui

QMAKE_CXXFLAGS += -std=c++17
CONFIG += console link_pkgconfig
CONFIG -= app_bundle

PKGCONFIG += gtest

INCLUDEPATH += ../main/

SOURCES += \
    ../main/mesh_loader.cc \
    main.cc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
