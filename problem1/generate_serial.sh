#!/bin/bash

# 基础命令
BASE_CMD="python generate_serial.py --model deepseek-chat --generate-times 25"

# 创建输出目录（如果不存在）
mkdir -p synthesis

# 启动 4 个后台进程，使用 nohup 防止 SIGHUP 信号终止
for i in {1..4}; do
  OUTPUT_DIR="./synthesis/gen-$i"
  mkdir -p "$OUTPUT_DIR"

  # 使用 nohup 后台运行，并重定向输出到日志文件
  nohup $BASE_CMD --output-dir "$OUTPUT_DIR" >"$OUTPUT_DIR/nohup.out" 2>&1 &

  echo "启动进程 $i，输出目录: $OUTPUT_DIR"
done

echo "所有进程已在后台启动！"
echo "可以使用 'ps aux | grep generate_serial.py' 查看进程状态"
echo "日志文件保存在各目录的 nohup.out 中"
