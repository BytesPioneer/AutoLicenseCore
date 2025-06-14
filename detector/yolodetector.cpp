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
