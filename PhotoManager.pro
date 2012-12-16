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
    imagecellchain.cpp

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
    imagecellchain.h

QT += sql

FORMS += \
    mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    image.qrc

unix{
    LIBS += -L $$_PRO_FILE_PWD_/thirdparty/opencv/lib
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_calib3d.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_core.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_features2d.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_flann.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_highgui.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_imgproc.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_legacy.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_ml.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_objdetect.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_photo.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_stitching.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_ts.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_video.so.2.4.3
    LIBS += $$_PRO_FILE_PWD_/thirdparty/opencv/lib/libopencv_videostab.so.2.4.3
}
win32{

}

unix{
    ParentDirectory = ../PhotoManager_tmp

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
    ParentDirectory = ..\PhotoManager_tmp

    RCC_DIR = "$$ParentDirectory\Build\RCCFiles"
    UI_DIR = "$$ParentDirectory\Build\UICFiles"
    MOC_DIR = "$$ParentDirectory\Build\MOCFiles"
    OBJECTS_DIR = "$$ParentDirectory\Build\ObjFiles"


    CONFIG(debug, debug|release) {
        DESTDIR = "$$ParentDirectory\debug"
    }
    CONFIG(release, debug|release) {
        DESTDIR = "$$ParentDirectory\release"
    }
}
