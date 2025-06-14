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
