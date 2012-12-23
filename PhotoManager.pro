SOURCES += \
    main.cpp \
    mainwindow.cpp \
    graphicsview.cpp \
    graphicsscene.cpp \
    cellitem.cpp \
    imageitem.cpp \
    confwidget.cpp \
    database.cpp \
    sortwidget.cpp \
    users.cpp \
    userschain.cpp \
    imagecellchain.cpp \
    dialogproperties.cpp

HEADERS += \
    mainwindow.h \
    graphicsview.h \
    graphicsscene.h \
    cellitem.h \
    imageitem.h \
    confwidget.h \
    database.h \
    sortwidget.h \
    users.h \
    userschain.h \
    imagecellchain.h \
    dialogproperties.h

QT += sql

FORMS += \
    mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    image.qrc


unix{
    INCLUDEPATH +=/usr/local/include/
    LIBS += -L/usr/local/lib
    LIBS += /usr/local/lib/libopencv_core.so
    LIBS += /usr/local/lib/libopencv_imgproc.so
    LIBS += /usr/local/lib/libopencv_highgui.so

    ParentDirectory = ../PhotoManager_build

    RCC_DIR = "$$ParentDirectory/Build/RCCFiles"
    UI_DIR = "$$ParentDirectory/Build/UICFiles"
    MOC_DIR = "$$ParentDirectory/Build/MOCFiles"
    OBJECTS_DIR = "$$ParentDirectory/Build/ObjFiles"


    CONFIG(debug, debug|release) {
        DESTDIR = "$$ParentDirectory/debug"
    }
    CONFIG(release, debug|release) {
        DESTDIR = "$$ParentDirectory/release"
    }
}

win32{
    INCLUDEPATH +=C:/OpenCv/build/release/include
    LIBS += -L C:/OpenCv/build/release/bin \
            -llibopencv_core243 \
            -llibopencv_imgproc243 \
            -llibopencv_highgui243

    ParentDirectory = ..\PhotoManager_build

    RCC_DIR = "$$ParentDirectory\\Build\\RCCFiles"
    UI_DIR = "$$ParentDirectory\\Build\\UICFiles"
    MOC_DIR = "$$ParentDirectory\\Build\\MOCFiles"
    OBJECTS_DIR = "$$ParentDirectory\\Build\\ObjFiles"


    CONFIG(debug, debug|release) {
        DESTDIR = "$$ParentDirectory\\debug"
    }
    CONFIG(release, debug|release) {
        DESTDIR = "$$ParentDirectory\\release"
    }
}
