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

    // std::vector<std::vector<std::vector<int>>> boxes;
    // cv::Mat img_vis=m_det->Run(srcimg, boxes);
    // std::vector<std::string> res=m_rec->Run(boxes, srcimg, nullptr);
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
