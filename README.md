# 基于Qt+OPenCV+YOLOv5+PaddleOCR的车牌识别检测系统开发全解析完整代码
#### 稀土掘金博客：https://juejin.cn/post/7515461483892015114

## 一.引言  

最近对机器视觉识别这个方向产生比较大的兴趣，想给自己安排一个学习计划来深度了解一下这个方向上所需要的技术栈，先给自己定一个目标-做一个与深度学习相关的并且入门难度不算太高的项目，在网上浏览了一大圈最终决定做一个基于深度学习的视觉检测车牌识别系统，看了一下目前网上大部分的方案都是采用Python语言开发的落地应用方案，作为一名C++程序员我决定用Qt+OPenCV+YOLOv5+PaddleOCR的方案实现一个完整的车牌检测识别系统，Qt构建用户交互界面，OPenCV负责图像技术处理，YOLOv5完成车牌检测大模型训练，PaddleOCR实现车牌图片的文本提取，这个项目准备分两个版本完成，核心功能如下：
v1.0版本 实现基于车牌图片实现识别检测（目前已完成）
v2.0版本 实现基于视频录像以及摄像头实时视频流的方向
- 开发平台：Windows/QtCreate
- 开发语言：Qt/C++
- 模型训练：Python/YOLOv5
- 图片处理：OPenCV
- 文字识别：PaddleOCR
话不多说，我们先来看看v1.0的成果
![image](https://github.com/user-attachments/assets/2dbe9d23-18e8-44c8-b377-1349dacb65da)

## 二.系统架构详解  

简单介绍一下项目系统代码架构，界面采用Qt6开发核心代码在MainWindow类中，车牌目标检测核心代码在detector目录的YoloDetector类中，车牌识别以及文本提取核心代码在ocr目录的IPaddleOCR类中，项目代码结构图如下
![image](https://github.com/user-attachments/assets/35702b32-3c97-49b2-80ca-18885b06a554)

### 1.主界面代码详解
函数功能说明  
上传文件：selectFile();  
开始检测：startDetect();  

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QFileDialog>
#include <QMessageBox>
#include <qpainter.h>
#include "detector/yolodetector.h"
#include "utils/imgutils.h"
#include "ocr/ipaddleocr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

/**
 *初始化
 */
void MainWindow::init()
{
    /*去掉标题栏*/
    this->setWindowFlags(Qt::FramelessWindowHint);
     /*显示屏幕中间*/
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    move((screenGeometry.width() - width()) / 2,
         (screenGeometry.height() - height()) / 2);

    /*日志输出*/
    logView = new LogTextEdit(this);
    logView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->layout_log->addWidget(logView);

    /*上传文件*/
    connect(ui->btn_file,&QPushButton::clicked,[=](){
        selectFile();
    });

    /*开始检测*/
    connect(ui->btn_detect,&QPushButton::clicked,[=](){
        startDetect();
    });

    /*退出系统*/
    connect(ui->btn_exit,&QPushButton::clicked,[=](){
        QApplication::quit();
    });
}

/**
 * 选择文件
 */
void MainWindow::selectFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "选择图片",
                                                    "",
                                                    "Images (*.png *.xpm *.jpg *.jpeg);;All Files (*)");
    if (!fileName.isEmpty()) {
        /*加载所选文件*/
        QPixmap pixmap(fileName);
        ui->label_source->setPixmap(pixmap.scaled(ui->label_source->size(),
                                                  Qt::KeepAspectRatio,
                                                  Qt::SmoothTransformation));
        ui->label_source->setAlignment(Qt::AlignCenter);
        srcImage=pixmap.toImage();
        this->logView->appendLog(QString("已选择文件"));
        qDebug()<<"Select Picture";
    }
}

/**
 * 开始检测
 */
void MainWindow::startDetect()
{
    if(srcImage.isNull())
    {
        QMessageBox::warning(this,"警告","请选择上传文件！");
        return;
    }

    YoloDetector yoloDetector;
    /*图像预处理*/
    this->logView->appendLog(QString("车牌检测中..."));
    cv::Mat preIamge=yoloDetector.preprocessImage(srcImage);
    auto plates = yoloDetector.detectPalte(preIamge);
    if (plates.empty()) {
        qDebug()<<"no detect plate";
        this->logView->appendLog(QString("未检测到车牌"));
        return ;
    }
    qDebug()<<"detect plate";
    this->logView->appendLog(QString("已检测到车牌"));
     /*已检测到目标区域*/
    cv::Rect plateRect = plates[0];
    QPixmap detectPixmap = QPixmap::fromImage(ImageUtils::cvMatToQImage(preIamge));
    /*绘制QPixmap*/
    QPainter painter(&detectPixmap);
     /*设置画笔颜色和宽度*/
    painter.setPen(QPen(Qt::green, 4));
    int x = static_cast<int>(plateRect.x );
    int y = static_cast<int>(plateRect.y );
    int width = static_cast<int>(plateRect.width );
    int height = static_cast<int>(plateRect.height );
    /*绘制区域以及宽高*/
    painter.drawRect(x, y, width, height);
    painter.end();
    /*显示车牌区域*/
    cv::Mat plateImage = preIamge(plates[0]);
    QImage displayImage=ImageUtils::cvMatToQImage(plateImage);
    ui->label_detect->setPixmap(QPixmap::fromImage(displayImage));
    ui->label_detect->setAlignment(Qt::AlignCenter);

    // cv::Mat ocrMat=ImageUtils::addBlackBackground(plateImage,plateImage.cols + 50,plateImage.rows + 50);
    cv::imwrite("ocrMat.png", plateImage);

    /*OCR识别结果*/
    this->logView->appendLog(QString("车牌识别中..."));
    IPaddleOCR ocr;
    QString result=ocr.ocrResult(plateImage);
    this->logView->appendLog(QString("车牌识别结果：%1").arg(result));
    this->ui->label_ocr_result->setText(result);
    qDebug()<<"ocr result:"<<result;
}

MainWindow::~MainWindow()
{
    delete ui;
}


2.目标检测
图像预处理：cv::Mat preprocessImage(const QImage& input);
YOLO目标检测：std::vectorcv::Rect detectPalte(cv::Mat &input);
车牌检测模型采用YOLOv5基于CCPD2020数据集进行训练，关于如何训练大模型的细节可以参考YOLOv5官方文档，网上也有很多的教程，需要注意的是最后训练得到的是基于PyTorch的模型如best.pt，而我这个项目中用的是基于ONNX推理的跨架构格式，所以训练得到best.pt后需要将其转换为best.onnx，通过OPenCV中的cv::dnn加载模型进行后续目标检测
#include "yolodetector.h"
#include "../utils/imgutils.h"
YoloDetector::YoloDetector()
{

}

/**
 * 图像预处理
 */
cv::Mat YoloDetector::preprocessImage(const QImage& image)
{
    cv::Mat mat = ImageUtils::qImageToMat(image);
    /*强制调整尺寸到640x640*/
    cv::Mat resized;
    cv::resize(mat, resized, cv::Size(640, 640));
    return resized;
}

/**
 * YOLO目标检测
 */
std::vector<cv::Rect> YoloDetector::detectPalte(cv::Mat &input)
{
    /*生成输入Blob（关键参数）必须与模型训练尺寸一致*/
    const cv::Size input_size(640, 640);
    /*归一化因子*/
    double scalefactor=1.0/255.0;
    cv::Mat blob = cv::dnn::blobFromImage(
        input,
        scalefactor,
        input_size,
        cv::Scalar(0,0,0),
        true,
        false
        );
    /*加载ONNX模型*/
    cv::dnn::Net net = cv::dnn::readNetFromONNX("best.onnx");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    net.setInput(blob);
    /*执行前向推理*/
    cv::Mat detections = net.forward();
    /*解析输出维度*/
    int num_detections = detections.size[1];  // 25200
    int num_params = detections.size[2];      // 6
    qDebug()<<"--num_detections:"<<num_detections<<"  --num_params"<<num_params;
    /*检测目标区域*/
    std::vector<cv::Rect> plates;
    cv::Mat outputs = detections.reshape(1, {num_detections, num_params});
    for (int i = 0; i < num_detections; ++i) {
        float* data = outputs.ptr<float>(i);

        float x_center = data[0];
        float y_center = data[1];
        float width = data[2];
        float height = data[3];
        float obj_score = data[4];
        float cls_score = data[5];

        int x1 = static_cast<int>(x_center - width / 2);
        int y1 = static_cast<int>(y_center - height / 2);
        int x2 = static_cast<int>(x_center + width / 2);
        int y2 = static_cast<int>(y_center + height /2);

        /*计算区域实际宽高*/
        int box_width = std::max(0, x2 - x1);
        int box_height = std::max(0, y2 - y1);
        float confidence = obj_score * cls_score;

        if (confidence > 0.25) {
            qDebug() << "Normalized values:"
                     << "x1:" << x1
                     << ", x2:" << x2
                     << "y1:" << y1
                     << ", y2:" << y2
                     << "x_center:" << x_center
                     << ", y_center:" << y_center
                     << ", width:" << width
                     << ", height:" << height
                     << ", Pixel box:" << x1 << "," << y1 << "," << box_width << "," << box_height;
            plates.emplace_back(x1, y1, box_width, box_height);
        }
    }
    return plates;
}

YoloDetector::~YoloDetector()
{
}
```

### 3.PaddleOCR车牌识别  
OCR识别结果提取：QString ocrResult(cv::Mat& srcimg);  
PaddleOCR官方教程：https://github.com/PaddlePaddle/PaddleOCR  

```c++
#include "ipaddleocr.h"
#include <QDebug>

IPaddleOCR::IPaddleOCR()
{
    init();
}

/**
 * 初始化
 */
void IPaddleOCR::init()
{
   PaddleOCR::OCRConfig config("config.txt");
   m_det=new PaddleOCR::DBDetector(config.det_model_dir, config.use_gpu, config.gpu_id,
                                      config.gpu_mem, config.cpu_math_library_num_threads,
                                      config.use_mkldnn, config.max_side_len, config.det_db_thresh,
                                      config.det_db_box_thresh, config.det_db_unclip_ratio,
                                      config.visualize, config.use_tensorrt, config.use_fp16);
   m_rec=new PaddleOCR::CRNNRecognizer(config.rec_model_dir, config.use_gpu, config.gpu_id,
                                          config.gpu_mem, config.cpu_math_library_num_threads,
                                          config.use_mkldnn, config.char_list_file,
                                          config.use_tensorrt, config.use_fp16);
}

/**
 * OCR识别结果
 */
QString IPaddleOCR::ocrResult(cv::Mat& srcimg)
{
    std::vector<std::vector<std::vector<int>>> boxes;
    std::vector<std::vector<int>> box = {
        {0, 0},
        {srcimg.cols, 0},
        {srcimg.cols, srcimg.rows},
        {0, srcimg.rows}
    };
    boxes.push_back(box);
    std::vector<std::string> res=m_rec->Run(boxes, srcimg, nullptr);

    QString result;
    for(auto s:res)
    {
        result.append(s.data());
    }
    qDebug()<<"result:"<<result;
    return result;
}

IPaddleOCR::~IPaddleOCR()
{
}
```

