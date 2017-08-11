# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = ComputerVee
QT       += core gui \
             widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComputerVee
TEMPLATE = app


HEADERS = \
   $$PWD/blob.h \
   $$PWD/coreprocess.h \
   $$PWD/counting.h \
   $$PWD/mainwindow.h \
   $$PWD/saver.h \
   $$PWD/videointerface.h \
    notify.h

SOURCES = \
   $$PWD/blob.cpp \
   $$PWD/coreprocess.cpp \
   $$PWD/counting.cpp \
   $$PWD/main.cpp \
   $$PWD/mainwindow.cpp \
   $$PWD/saver.cpp \
   $$PWD/videointerface.cpp \
    notify.cpp

INCLUDEPATH += /usr/include/opencv \
    $$PWD/.

#DEFINES = 


LIBS += -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core
FORMS += mainwindow.ui
QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS += -O3 -mpreferred-stack-boundary=5 -finline-small-functions -momit-leaf-frame-pointer
QMAKE_CXXFLAGS += -finline-small-functions -momit-leaf-frame-pointer -flto -march=native

