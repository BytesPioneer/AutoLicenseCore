// Copyright (c) 2020 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "paddle_api.h"
#include "paddle_inference_api.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

#include <cstring>
#include <fstream>
#include <numeric>

#include "ocr_cls.h"
#include "postprocess_op.h"
#include "preprocess_op.h"
#include "utility.h"

using namespace paddle_infer;

namespace PaddleOCR {

class CRNNRecognizer {
public:
  explicit CRNNRecognizer(const std::string &model_dir, const bool &use_gpu,
                          const int &gpu_id, const int &gpu_mem,
                          const int &cpu_math_library_num_threads,
                          const bool &use_mkldnn, const string &label_path,
                          const bool &use_tensorrt, const bool &use_fp16) {
    this->use_gpu_ = use_gpu;
    this->gpu_id_ = gpu_id;
    this->gpu_mem_ = gpu_mem;
    this->cpu_math_library_num_threads_ = cpu_math_library_num_threads;
    this->use_mkldnn_ = use_mkldnn;
    this->use_tensorrt_ = use_tensorrt;
    this->use_fp16_ = use_fp16;

    this->label_list_ = Utility::ReadDict(label_path);
    this->label_list_.insert(this->label_list_.begin(),
                             "#"); // blank char for ctc
    this->label_list_.push_back(" ");

    LoadModel(model_dir);
  }

  // Load Paddle inference model
  void LoadModel(const std::string &model_dir);

  std::vector<std::string> Run(std::vector<std::vector<std::vector<int>>> boxes, cv::Mat &img,
           Classifier *cls);

private:
  std::shared_ptr<Predictor> predictor_;

  bool use_gpu_ = false;
  int gpu_id_ = 0;
  int gpu_mem_ = 4000;
  int cpu_math_library_num_threads_ = 4;
  bool use_mkldnn_ = false;

  std::vector<std::string> label_list_;

  std::vector<float> mean_ = {0.5f, 0.5f, 0.5f};
  std::vector<float> scale_ = {1 / 0.5f, 1 / 0.5f, 1 / 0.5f};
  bool is_scale_ = true;
  bool use_tensorrt_ = false;
  bool use_fp16_ = false;
  // pre-process
  CrnnResizeImg resize_op_;
  Normalize normalize_op_;
  Permute permute_op_;

  // post-process
  PostProcessor post_processor_;

  cv::Mat GetRotateCropImage(const cv::Mat &srcimage,
                             std::vector<std::vector<int>> box);

}; // class CrnnRecognizer

} // namespace PaddleOCR
