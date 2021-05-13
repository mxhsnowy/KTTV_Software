QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
RC_ICONS = KttvIconCrop.ico
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    extractandreport.cpp \
    graphicsitems.cpp \
    input.cpp \
    linedetection.cpp \
    main.cpp \
    mainwindow.cpp \
    mygraphicsitem.cpp \
    mygraphicsview.cpp

HEADERS += \
    convert.h \
    extractandreport.h \
    graphicsitems.h \
    input.h \
    linedetection.h \
    mainwindow.h \
    mygraphicsitem.h \
    mygraphicsview.h \
    somefuntions.h

FORMS += \
    input.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Icon.qrc
win32:CONFIG(release, debug|release): LIBS += -L"E:/opencv_4.5.1/opencv/build/x64/vc15/lib" -lopencv_world451
else:win32:CONFIG(debug, debug|release): LIBS += -L"E:/opencv_4.5.1/opencv/build/x64/vc15/lib" -lopencv_world451d

INCLUDEPATH += "E:/opencv_4.5.1/opencv/build/include"

DEPENDPATH += "E:/opencv_4.5.1/opencv/build/include"
