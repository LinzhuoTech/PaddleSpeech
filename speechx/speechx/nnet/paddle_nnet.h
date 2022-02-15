
#pragma once

#include "nnet/nnet_interface.h"
#include "base/common.h"
#include "paddle/paddle_inference_api.h"


namespace ppspeech {

struct ModelOptions {
  std::string model_path;
  std::string params_path;
  int thread_num;
  bool use_gpu;
  bool switch_ir_optim;
  std::string input_names;
  std::string output_names;
  std::string cache_names;
  std::string cache_shape;
  bool enable_fc_padding;
  bool enable_profile;
  ModelDecoderOptions() : 
      model_path("model/final.zip"),
      params_path("model/avg_1.jit.pdmodel"),
      thread_num(2),
      use_gpu(false),
      input_names("audio"),
      output_names("probs"),
      cache_names("enouts"),
      cache_shape("1-1-1"),
      switch_ir_optim(false),
      enable_fc_padding(false),
      enable_profile(false) {
  }

  void Register(kaldi::OptionsItf* opts) {
    opts->Register("model-path", &model_path, "model file path");
    opts->Register("model-params", &params_path, "params model file path");
    opts->Register("thread-num", &thread_num, "thread num");
    opts->Register("use-gpu", &use_gpu, "if use gpu");
    opts->Register("input-names", &input_names, "paddle input names");
    opts->Register("output-names", &output_names, "paddle output names");
    opts->Register("cache-names", &cache_names, "cache names");
    opts->Register("cache-shape", &cache_shape, "cache shape");
    opts->Register("switch-ir-optiom", &switch_ir_optim, "paddle SwitchIrOptim option");
    opts->Register("enable-fc-padding", &enable_fc_padding, "paddle EnableFCPadding option");
    opts->Register("enable-profile", &enable_profile, "paddle EnableProfile option");
  }
};

    void Register(kaldi::OptionsItf* opts) {
        _model_opts.Register(opts);
        opts->Register("subsampling-rate", &subsampling_rate, 
                       "subsampling rate for deepspeech model");
        opts->Register("receptive-field-length", &receptive_field_length, 
                       "receptive field length for deepspeech model");
    }
};


template<typename T>
class Tensor {
public:
    Tensor() {
    }
    Tensor(const std::vector<int>& shape) :
        _shape(shape) {
        int data_size = std::accumulate(_shape.begin(), _shape.end(),
                                            1, std::multiplies<int>());
        LOG(INFO) << "data size: " << data_size;
        _data.resize(data_size, 0);
    }
    void reshape(const std::vector<int>& shape) {
        _shape = shape;
        int data_size = std::accumulate(_shape.begin(), _shape.end(),
                                        1, std::multiplies<int>());
        _data.resize(data_size, 0);
    }
    const std::vector<int>& get_shape() const {
        return _shape;
    }
    std::vector<T>& get_data() {
        return _data;
    }
private:
    std::vector<int> _shape;
    std::vector<T> _data;
};

class PaddleNnet : public NnetInterface {
  public:
    PaddleNnet(const ModelOptions& opts);
    virtual void FeedForward(const kaldi::Matrix<BaseFloat>& features, 
                             kaldi::Matrix<kaldi::BaseFloat>* inferences) const;
    std::shared_ptr<Tensor<kaldi::BaseFloat>> GetCacheEncoder(const std::string& name);
    void init_cache_encouts(const ModelOptions& opts); 
    
  private:
    std::unique_ptr<paddle_infer::services::PredictorPool> pool;
    std::vector<bool> pool_usages;
    std::mutex pool_mutex;
    std::map<std::string, int> cache_names_idx_;
    std::vector<std::shared_ptr<Tensor<kaldi::BaseFloat>>> cache_encouts_;

  public:
    DISALLOW_COPY_AND_ASSIGN(PaddleNnet);
};

} // namespace ppspeech                                                                                                                                                                                                                             
