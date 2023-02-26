QT             += core gui widgets opengl openglwidgets concurrent

win32 {
LIBS           += -lopengl32 -lglu32
}

CONFIG         += c++17 optimize_full
QMAKE_CXXFLAGS += -std=c++17

include(shared/qtgifimage/src/gifimage/qtgifimage.pri)

INCLUDEPATH    += models/ views/

SOURCES        +=                      \
    main.cc                            \
    views/main_form.cc                 \
    views/opengl_widget.cc             \
    models/viewer.cc                   \
    models/settings/settings.cc        \
    models/image-saver/image_saver.cc  \
    models/mesh-loader/mesh_loader.cc  \
    models/transformer/transformer.cc  \
    models/renderers/wired_renderer.cc

HEADERS        +=                      \
    controller.h                       \
    views/main_form.h                  \
    views/opengl_widget.h              \
    models/viewer.h                    \
    models/mesh.h                      \
    models/settings/settings.h         \
    models/image-saver/image_saver.h   \
    models/mesh-loader/mesh_loader.h   \
    models/transformer/transformer.h   \
    models/renderers/base_renderer.h   \
    models/renderers/renderer.h        \
    models/renderers/wired_renderer.h

FORMS          += views/mainform.ui

RESOURCES      += shaders/shaders.qrc
