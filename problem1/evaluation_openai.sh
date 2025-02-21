models=("gpt-4o-mini" "gpt-4o")

for model in "${models[@]}"; do
    python evaluation.py --codes-dir ./logs/$model --output-dir ./datas/$model --processes 1 --eval-times 1
