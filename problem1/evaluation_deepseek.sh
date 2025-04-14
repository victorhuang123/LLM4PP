models=("deepseek-chat" "deepseek-reasoner")

for model in "${models[@]}"; do
    python evaluation.py --codes-dir ./logs/$model --output-dir ./datas/$model --eval-times 1
done
