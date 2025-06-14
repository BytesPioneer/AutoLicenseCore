#ifndef YOLODETECTOR_H
#define YOLODETECTOR_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <QImage>
class YoloDetector{
public:
    YoloDetector();
    ~YoloDetector();
    /**
     * 图像预处理
     */
    cv::Mat preprocessImage(const QImage& input);

    /**
     * YOLO目标检测
     */
    std::vector<cv::Rect> detectPalte(cv::Mat &input);
private:

};
#endif
