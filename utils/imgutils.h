#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <QImage>
#include <QDebug>
class ImageUtils
{
public:

    /**
     * Mat转QImage
     */
    static QImage cvMatToQImage(const cv::Mat &mat) {
        // 检查输入有效性
        if (mat.empty()) {
            qWarning() << "输入cv::Mat为空!";
            return QImage();
        }

        // 处理不同通道类型的转换
        switch (mat.channels()) {
        case 1: { // 灰度图
            QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
            image.setColorCount(256);
            for (int i = 0; i < 256; ++i) {
                image.setColor(i, qRgb(i, i, i));
            }
            return image.copy(); // 必须复制，避免悬垂指针
        }
        case 3: { // BGR转RGB
            cv::Mat rgbMat;
            cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
            return QImage(rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_RGB888).copy();
        }
        case 4: { // BGRA转RGBA
            cv::Mat rgbaMat;
            cv::cvtColor(mat, rgbaMat, cv::COLOR_BGRA2RGBA);
            return QImage(rgbaMat.data, rgbaMat.cols, rgbaMat.rows, rgbaMat.step, QImage::Format_RGBA8888).copy();
        }
        default: {
            qWarning() << "不支持的通道数:" << mat.channels();
            return QImage();
        }
        }
    }

    /**
     * QImage转Mat
     */
    static cv::Mat qImageToMat(const QImage &image) {
        cv::Mat mat;
        switch (image.format()) {
        case QImage::Format_RGB32: {
            // 4通道转3通道（丢弃Alpha通道）
            mat = cv::Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
            cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGR); // 转换为BGR并去Alpha
            break;
        }
        case QImage::Format_RGB888: {
            mat = cv::Mat(image.height(), image.width(), CV_8UC3, const_cast<uchar*>(image.bits()), image.bytesPerLine());
            cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR); // 转换为BGR
            break;
        }
        case QImage::Format_ARGB32: {
            mat = cv::Mat(image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine());
            cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR); // 处理带Alpha通道的情况
            break;
        }
        default: {
            // 强制转换为RGB888再转BGR
            image.convertToFormat(QImage::Format_RGB888).bits();
            mat = cv::Mat(image.height(), image.width(), CV_8UC3,const_cast<uchar*>(image.bits()), image.bytesPerLine());
            cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
            break;
        }
        }
        return mat;
    }

    static cv::Mat addBlackBackground(const cv::Mat& inputImage, int targetWidth, int targetHeight)
    {
        // 验证输入图像是否有效
        if(inputImage.empty()) {
            qDebug() << "错误: 输入图像为空";
            return cv::Mat();
        }

        // 检查目标尺寸是否合理
        if(targetWidth < inputImage.cols || targetHeight < inputImage.rows) {
            qDebug() << "警告: 目标尺寸小于输入图像 ("
                     << inputImage.cols << "x" << inputImage.rows << ")"
                     << "使用当前尺寸：" << targetWidth << "x" << targetHeight;
        }

        // 创建目标尺寸的黑色背景
        cv::Mat result(targetHeight, targetWidth, inputImage.type(), cv::Scalar(0, 0, 0));

        // 计算放置原图的起始位置（居中）
        int startX = (targetWidth - inputImage.cols) / 2;
        int startY = (targetHeight - inputImage.rows) / 2;

        // 验证位置是否有效
        if(startX < 0 || startY < 0) {
            qDebug() << "错误: 目标尺寸小于图像尺寸";
            return cv::Mat();
        }

        // 将原图复制到黑色背景上
        cv::Rect roi(startX, startY, inputImage.cols, inputImage.rows);
        inputImage.copyTo(result(roi));

        return result;
    }
};
#endif
