QT             -= gui

QMAKE_CXXFLAGS += -std=c++17
CONFIG         += console link_pkgconfig
CONFIG         -= app_bundle

PKGCONFIG      += gtest

INCLUDEPATH    += ../main/models

SOURCES        +=                             \
    ../main/models/mesh-loader/mesh_loader.cc \
    main.cc
