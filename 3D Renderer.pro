QT       += core gui network

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

INCLUDEPATH += ./include

SOURCES += \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/conemodellistwidgetitem.cpp \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/colormodellistwidgetitem.cpp \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/cylindermodellistwidgetitem.cpp \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/spheremodellistwidgetitem.cpp \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/conemodelpropertieswidget.cpp \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/cylindermodelpropertieswidget.cpp \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/spheremodelpropertieswidget.cpp \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/colormodelpropertieswidget.cpp \
    src/GUI/MainWindow/listwidget.cpp \
    src/GUI/MainWindow/ListWidget/listwidgetitem.cpp \
    src/GUI/aboutdialog.cpp \
    src/GUI/qssloader.cpp \
    src/GUI/settingswidget.cpp \
    src/GUI/sliderfloat.cpp \
    src/OpenGL/Models/colormodel.cpp \
    src/OpenGL/Models/gridmodel.cpp \
    src/OpenGL/Shaders/gridshader.cpp \
    src/OpenGL/Shaders/lightshader.cpp \
    src/OpenGL/camera.cpp \
    src/OpenGL/light.cpp \
    src/OpenGL/model.cpp \
    src/OpenGL/texture.cpp \
    src\OpenGL\shader.cpp \
    src/GUI/MainWindow/glwidget.cpp \
    src/main.cpp \
    src/GUI/mainwindow.cpp \
    src/OpenGL/mesh.cpp \
    src/GUI/MainWindow/ListWidget/modelpropertieswidget.cpp \
    src/GUI/sliderint.cpp

HEADERS += \
    lib/stb_image.h \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/conemodellistwidgetitem.h \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/colormodellistwidgetitem.h \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/cylindermodellistwidgetitem.h \
    src/GUI/MainWindow/ListWidget/ListWidgetItem/spheremodellistwidgetitem.h \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/conemodelpropertieswidget.h \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/cylindermodelpropertieswidget.h \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/spheremodelpropertieswidget.h \
    src/GUI/MainWindow/ListWidget/ModelPropertiesWidget/colormodelpropertieswidget.h \
    src/GUI/MainWindow/listwidget.h \
    src/GUI/MainWindow/ListWidget/listwidgetitem.h \
    src/GUI/aboutdialog.h \
    src/GUI/settingswidget.h \
    src/GUI/sliderfloat.h \
    src/OpenGL/Models/colormodel.h \
    src/OpenGL/Models/gridmodel.h \
    src/OpenGL/Shaders/gridshader.h \
    src/OpenGL/Shaders/lightshader.h \
    src/OpenGL/camera.h \
    src/OpenGL/light.h \
    src/OpenGL/model.h \
    src/OpenGL/texture.h \
    src/OpenGL/vertex.h \
    src/OpenGL/shader.h \
    src/GUI/MainWindow/glwidget.h \
    src/GUI/mainwindow.h \
    src/OpenGL/mesh.h \
    src/GUI/MainWindow/ListWidget/modelpropertieswidget.h \
    src/GUI/sliderint.h \
    src/GUI/qssloader.h \
    src/version.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = etc/appicon.ico

RESOURCES += \
    Resources.qrc
