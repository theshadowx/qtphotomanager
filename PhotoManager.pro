SOURCES += \
    src/userschain.cpp \
    src/users.cpp \
    src/sortwidget.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/imageitem.cpp \
    src/imagecellchain.cpp \
    src/histogram.cpp \
    src/graphicsview.cpp \
    src/graphicsscene.cpp \
    src/dialogproperties.cpp \
    src/databasewidget.cpp \
    src/database.cpp \
    src/confwidget.cpp \
    src/comboboxdelegate.cpp \
    src/cellitem.cpp \
    src/filterkerneldialog.cpp \
    src/previewwidget.cpp \
    src/piechart.cpp \
    src/minmaxdialog.cpp

HEADERS += \
    src/userschain.h \
    src/users.h \
    src/sortwidget.h \
    src/mainwindow.h \
    src/imageitem.h \
    src/imagecellchain.h \
    src/histogram.h \
    src/graphicsview.h \
    src/graphicsscene.h \
    src/dialogproperties.h \
    src/databasewidget.h \
    src/database.h \
    src/confwidget.h \
    src/comboboxdelegate.h \
    src/cellitem.h \
    src/filterkerneldialog.h \
    src/previewwidget.h \
    src/piechart.h \
    src/minmaxdialog.h

FORMS += \
    ui/mainwindow.ui \
    ui/filterkerneldialog.ui

OTHER_FILES += \
    icon/qt-logo.png \
    res/stylesheet/stylesheet.qss

RESOURCES += \
    res/resources.qrc

INCLUDEPATH +=./include


OpenCv = /home/theshadowx/workspace/Project_QT/openCV/OpenCv/Release

unix{
    INCLUDEPATH +=$$OpenCv/include/
    LIBS += -L$$OpenCv/lib
    LIBS += $$OpenCv/lib/libopencv_core.so.2.4
    LIBS += $$OpenCv/lib/libopencv_imgproc.so.2.4
    LIBS += $$OpenCv/lib/libopencv_highgui.so.2.4

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

    INCLUDEPATH += $$OpenCv/include
    LIBS += -L $$OpenCv/bin \
            -llibopencv_core243 \
            -llibopencv_imgproc243 \
            -llibopencv_highgui243

    ParentDirectory = ../PhotoManager_build

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
