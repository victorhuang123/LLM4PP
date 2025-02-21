#!/bin/bash
models=("gpt-4o-mini" "gpt-4o")

for model in "${models[@]}"; do
    #--------------------------------------------------#
    echo 'base'
    python generate.py --models $model
    python generate.py --models $model --check true
    #--------------------------------------------------#

    #--------------------------------------------------#
    echo 's-p norag'
    python generate.py --models $model --two-stage true --serial-rag false --parallel-rag false
    python generate.py --models $model --two-stage true --serial-rag false --parallel-rag false --check true
    #--------------------------------------------------#

    #--------------------------------------------------#
    echo 's rag then p'
    python generate.py --models $model --two-stage true --serial-rag true --parallel-rag false
    python generate.py --models $model --two-stage true --serial-rag true --parallel-rag false --check true
    #--------------------------------------------------#

    #--------------------------------------------------#
    echo 's rag p rag'
    python generate.py --models $model --two-stage true --serial-rag true --parallel-rag true
    python generate.py --models $model --two-stage true --serial-rag true --parallel-rag true --check true
    #--------------------------------------------------#
done
