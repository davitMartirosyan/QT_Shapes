QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    factory/FactoryLine.cpp \
    factory/FactoryRect.cpp \
    factory/FactoryTriangle.cpp \
    main.cpp \
    mainwindow.cpp \
    parser/Parser.cpp \
    shape/Line.cpp \
    shape/Rect.cpp \
    shape/Shape.cpp \
    shape/Triangle.cpp

HEADERS += \
    factory/Factory.h \
    factory/FactoryLine.h \
    factory/FactoryRect.h \
    factory/FactoryTriangle.h \
    mainwindow.h \
    parser/Parser.h \
    shape/Line.h \
    shape/Rect.h \
    shape/Shape.h \
    shape/ShapeData.h \
    shape/Triangle.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
