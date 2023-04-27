#!/bin/bash

config_path=$1
train_output_path=$2
ckpt_name=$3

FLAGS_allocator_strategy=naive_best_fit \
FLAGS_fraction_of_gpu_memory_to_use=0.01 \
python3 ../../../paddlespeech/t2s/exps/synthesize_e2e.py \
    --am=fastspeech2_mix \
    --am_config=../../zh_en_tts/tts3/exp/default/default.yaml \
    --am_ckpt=../../zh_en_tts/tts3/exp/default/checkpoints/snapshot_iter_1144455.pdz \
    --am_stat=../../zh_en_tts/tts3/dump/train/speech_stats.npy \
    --voc=mb_melgan_csmsc \
    --voc_config=${config_path} \
    --voc_ckpt=${train_output_path}/checkpoints/${ckpt_name} \
    --voc_stat=dump/train/feats_stats.npy \
    --lang=mix \
    --text=../../../paddlespeech/t2s/exps/sentences_mix.txt \
    --output_dir=${train_output_path}/test_e2e \
    --phones_dict=../../zh_en_tts/tts3/dump/phone_id_map.txt \
    --speaker_dict=../../zh_en_tts/tts3/dump/speaker_id_map.txt \
    --spk_id=174 \
    --inference_dir=${train_output_path}/inference
