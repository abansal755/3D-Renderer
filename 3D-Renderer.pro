QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += lib/glm

SOURCES += \
    src/GUI/MainWindow/glwidget.cpp \
    src/main.cpp \
    src/GUI/mainwindow.cpp \
    src/OpenGL/Lights/directionallight.cpp \
    src/OpenGL/Shaders/lightshader.cpp \
    src/OpenGL/camera.cpp \
    src/OpenGL/mesh.cpp \
    src/OpenGL/model.cpp \
    src/OpenGL/shader.cpp \
    src/OpenGL/texture.cpp

HEADERS += \
    src/GUI/MainWindow/glwidget.h \
    src/GUI/mainwindow.h \
    src/OpenGL/Lights/directionallight.h \
    src/OpenGL/Shaders/lightshader.h \
    src/OpenGL/camera.h \
    src/OpenGL/light.h \
    src/OpenGL/material.h \
    src/OpenGL/mesh.h \
    src/OpenGL/model.h \
    src/OpenGL/shader.h \
    src/OpenGL/texture.h \
    src/OpenGL/vertex.h \
    lib/stb_image.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/OpenGL/Shaders/flatshader.frag \
    src/OpenGL/Shaders/flatshader.vert
