QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    detector/yolodetector.cpp \
    logtextedit.cpp \
    main.cpp \
    mainwindow.cpp \
    ocr/ipaddleocr.cpp \
    ocr/paddle/clipper.cpp \
    ocr/paddle/config.cpp \
    ocr/paddle/ocr_cls.cpp \
    ocr/paddle/ocr_det.cpp \
    ocr/paddle/ocr_rec.cpp \
    ocr/paddle/postprocess_op.cpp \
    ocr/paddle/preprocess_op.cpp \
    ocr/paddle/utility.cpp \
    detector/yolodetector.cpp \

HEADERS += \
    detector/yolodetector.h \
    logtextedit.h \
    mainwindow.h \
    ocr/ipaddleocr.h \
    ocr/paddle/clipper.h \
    ocr/paddle/config.h \
    ocr/paddle/ocr_cls.h \
    ocr/paddle/ocr_det.h \
    ocr/paddle/ocr_rec.h \
    ocr/paddle/postprocess_op.h \
    ocr/paddle/preprocess_op.h \
    ocr/paddle/utility.h \
    detector/yolodetector.h \
    utils/imgutils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LE:/Appication/opencv/build/x64/vc16/lib/ -lopencv_world4110
else:win32:CONFIG(debug, debug|release): LIBS += -LE:/Appication/opencv/build/x64/vc16/lib/ -lopencv_world4110d

INCLUDEPATH += E:/Appication/opencv/build/include
DEPENDPATH += E:/Appication/opencv/build/include

DISTFILES += \
    model/yolo/best.onnx

PADDLE_PATH = E:/Appication/C++/paddle_inference

INCLUDEPATH +=$$PADDLE_PATH/paddle/include \
    $$PADDLE_PATH/third_party/install/cryptopp/include \
    $$PADDLE_PATH/third_party/install/glog/include \
    $$PADDLE_PATH/third_party/install/mkldnn/include \
    $$PADDLE_PATH/third_party/install/mklml/include \
    $$PADDLE_PATH/third_party/install/protobuf/include \
    $$PADDLE_PATH/third_party/install/xxhash/include

LIBS += -L$$PADDLE_PATH/paddle/lib -lpaddle_inference
LIBS += -L$$PADDLE_PATH/third_party/install/glog/lib/glog.lib
LIBS += -L$$PADDLE_PATH/third_party/install/mkldnn/lib -lmkldnn
LIBS += -L$$PADDLE_PATH/third_party/install/mklml/lib -llibiomp5md -lmklml
LIBS += -L$$PADDLE_PATH/third_party/install/protobuf/lib/libprotobuf.lib
LIBS += -L$$PADDLE_PATH/third_party/install/xxhash/lib/xxhash.lib
LIBS += -L$$PADDLE_PATH/third_party/install/mkldnn/lib
LIBS += -L$$PADDLE_PATH/third_party/install/mklml/lib
