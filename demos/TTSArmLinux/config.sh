# configuration

ARM_ABI=armv8
#ARM_ABI=armv7hf

MODELS_DIR="${PWD}/models"
LIBS_DIR="${PWD}/libs"
OUTPUT_DIR="${PWD}/output"

PADDLE_LITE_DIR="${LIBS_DIR}/inference_lite_lib.armlinux.${ARM_ABI}.gcc.with_extra.with_cv/cxx"
#PADDLE_LITE_DIR="/path/to/Paddle-Lite/build.lite.linux.${ARM_ABI}.gcc/inference_lite_lib.armlinux.${ARM_ABI}/cxx"

# 声学模型
ACOUSTIC_MODEL_PATH="${MODELS_DIR}/cpu/fastspeech2_mix_static_0.2.0.nb"
# 说话人ID
# 如果模型不支持多说话人，必须留空，如果支持则必须设置，否则程序可能会崩溃
SPEAKER_ID="1"
# 数据类型需要与模型匹配，否则程序可能会崩溃
SPEAKER_ID_DATA_TYPE="int64"
PHONE_ID_DATA_TYPE="int64"

# 声码器模型
VOCODER_PATH="${MODELS_DIR}/cpu/mb_melgan_csmsc_static_0.1.1.nb"

# 文本前端的配置文件
FRONT_CONF="${PWD}/front.conf"
