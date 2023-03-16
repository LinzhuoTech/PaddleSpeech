#!/bin/bash
set -e

cd "$(dirname "$(realpath "$0")")"

# load configure
. ./config.sh

# create dir
mkdir -p "$OUTPUT_DIR"

# run
set -x
./build/paddlespeech_tts_demo \
    --front_conf "$FRONT_CONF" \
    --acoustic_model "$ACOUSTIC_MODEL_PATH" \
    --speaker_id "$SPEAKER_ID" \
    --speaker_id_data_type "$SPEAKER_ID_DATA_TYPE" \
    --phone_id_data_type "$PHONE_ID_DATA_TYPE" \
    --vocoder "$VOCODER_PATH" \
    "$@"
# end
