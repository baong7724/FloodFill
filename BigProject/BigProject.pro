QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    displayhandle.cpp \
    floodfill.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow1.cpp

HEADERS += \
    dialog.h \
    displayhandle.h \
    floodfill.h \
    mainwindow.h \
    mainwindow1.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    mainwindow1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../../opencv/build/x64/vc16/lib/ -lopencv_world470
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../../opencv/build/x64/vc16/lib/ -lopencv_world470d
else:unix: LIBS += -L$$PWD/../../../../../../../../../opencv/build/x64/vc16/lib/ -lopencv_world470

INCLUDEPATH += $$PWD/../../../../../../../../../opencv/build/include
DEPENDPATH += $$PWD/../../../../../../../../../opencv/build/include

RESOURCES += \
    Resource.qrc

DISTFILES +=
