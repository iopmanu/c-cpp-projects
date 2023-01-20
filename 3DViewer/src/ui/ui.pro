QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

LDFLAGS += -Wl,-V

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    engine.cpp \
    main.cpp \
    mainwindow.cpp \
    ../obj_parser/parser.c \
    ../matrix/matrix.c \
    ../affine_transformations/transformations.c


HEADERS += \
    engine.hpp \
    mainwindow.h \
    ../obj_parser/parser.h \
    ../matrix/matrix.h \
    ../affine_transformations/transformation.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
