#-------------------------------------------------
#
# Project created by QtCreator 2016-10-24T18:42:48
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjViewer
TEMPLATE = app

#LIBS += external/tinyobjloader/tiny_obj_loader.h
#LIBS += external/glm/glm.hpp


SOURCES += src/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/mainglwidget.cpp \
    src/brush/brush.cpp \
    src/brush/model/geometry.cpp \
    src/controller.cpp \
    src/brush/abstractbrush.cpp \
    src/brush/slowraysbrush.cpp \
    src/brush/pixelspaintingbrush.cpp \
    src/brush/brushstroke.cpp \
    src/brush/brushhistory.cpp \
    src/brush/pixelsfastbrush.cpp \
    src/brush/model/color.cpp \
    src/brush/model/idsstorage.cpp \
    src/brush/model/texturestorage.cpp \
    src/brush/model/objectmodel.cpp

HEADERS += src/ui/mainwindow.h \
    src/ui/mainglwidget.h \
    src/vertex.h \
    src/brush/brush.h \
    src/brush/model/geometry.h \
    src/controller.h \
    src/brush/abstractbrush.h \
    src/brush/slowraysbrush.h \
    src/brush/pixelspaintingbrush.h \
    src/brush/brushstroke.h \
    src/brush/brushhistory.h \
    src/brush/pixelsfastbrush.h \
    src/brush/model/color.h \
    src/brush/model/idsstorage.h \
    src/brush/model/texturestorage.h \
    src/brush/model/objectmodel.h

FORMS   += src/ui/mainwindow.ui

INCLUDEPATH += \
    src/ \
    src/ui/ \
    src/brush/ \
    src/brush/model/ \
    external/tinyobjloader/ \
    external/glm/

OTHER_FILES += \
    external/tinyobjloader/tiny_obj_loader.h \
    resources/cube.obj \
    resources/simple_texture.bmp \
    resources/shaders/vshader.glsl \
    resources/shaders/fshader.glsl \
    resources/shaders/vshaderForIds.glsl \
    resources/shaders/fshaderForIds.glsl \

RESOURCES += \
    resources.qrc

DISTFILES += \
    .gitignore \
    fshaderForIds.glsl

