QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
   ../s21_calculation/s21_calculation.c \
    ../parser/s21_parser.c \
    ../parser/s21_helper_parser.c \
    ../data_structure/s21_stack.c \
    qcustomplot.cpp

HEADERS += \
    graph.h \
    mainwindow.h \
    ../s21_calculation/s21_calculation.h \
    ../parser/s21_parser.h \
    ../parser/s21_helper_parser.h \
    ../data_structure/s21_stack.h \
    qcustomplot.h

FORMS += \
    graph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
