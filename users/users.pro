QT += core gui sql widgets multimedia
QT       += printsupport
QT += charts
QT += network quickwidgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connexion.cpp \
    csports.cpp \
    equipement.cpp \
    event.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowlogin.cpp \
    openweathermapforecast.cpp \
    qrcode.cpp \
    sportif.cpp \
    use.cpp \
    user.cpp

HEADERS += \
    arduino.h \
    connexion.h \
    csports.h \
    equipement.h \
    event.h \
    mainwindow.h \
    mainwindowlogin.h \
    openweathermapforecast.h \
    qrcode.h \
    sportif.h \
    use.h \
    user.h

FORMS += \
    mainwindow.ui \
    mainwindowlogin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT+=sql

RESOURCES += \
    assets.qrc

DISTFILES += \
    ../../../Downloads/426886963_1092037198703715_251700748182099265_n.png
#include(C:\Users\DOUA\Downloads\opencv-4.9.0-\opencv-4.9.0\opencv_library_path.txt)

#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_highgui490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_imgcodecs490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_imgproc490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_core490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_objdetect490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_dnn_objdetect490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_dnn490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_dnn_superres490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_features2d490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_xfeatures2d490.dll
#win32: LIBS += -L$$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/x64/mingw/lib/ -llibopencv_xobjdetect490.dll



#INCLUDEPATH += $$PWD/../../../Downloads/opencv-4.9.0-/opencv-4.9.0/build/install/include
#DEPENDPATH += $$PWD/../../../Downloads/opencv-4.9.0-/opencv-4.9.0/build/install/include


INCLUDEPATH += $$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/include
DEPENDPATH += $$PWD/../../../opencv-4.9.0-/opencv-4.9.0/build/install/include
