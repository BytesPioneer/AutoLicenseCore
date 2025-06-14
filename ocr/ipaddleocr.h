#ifndef IPADDLEOCR_H
#define IPADDLEOCR_H
#include "paddle/config.h"
#include "paddle/ocr_det.h"
#include "paddle/ocr_rec.h"
#include <QString>
#include <opencv2/core/core.hpp>
class IPaddleOCR{
public:
    IPaddleOCR();
    ~IPaddleOCR();
    void init();
    QString ocrResult(cv::Mat& srcimg);
private:
    PaddleOCR::DBDetector* m_det;
    PaddleOCR::CRNNRecognizer* m_rec;
    void* ocrHandle;
};
#endif
