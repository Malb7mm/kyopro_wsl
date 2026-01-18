#!/bin/bash

# 設定
WATCH_DIR="./snippets"
UPDATE_SCRIPT="./sref.sh"

# 依存コマンドのチェック
if ! command -v inotifywait &> /dev/null; then
    echo "Error: inotifywait not found. Please run 'sudo apt install inotify-tools'"
    exit 1
fi

if [ ! -x "$UPDATE_SCRIPT" ]; then
    echo "Error: $UPDATE_SCRIPT is not executable or not found."
    echo "Run 'chmod +x $UPDATE_SCRIPT' to fix permissions."
    exit 1
fi

echo "Start watching $WATCH_DIR ..."

# 初回実行（念のため起動時にも更新しておく）
$UPDATE_SCRIPT

# 監視ループ
# -m: モニターモード（終了せずに監視し続ける）
# -r: 再帰的（サブディレクトリも監視）
# -e: 監視するイベント（書き込み完了、移動、作成、削除）
# --format: 出力を簡潔にする（バッファリング対策）
inotifywait -m -r -e close_write,moved_to,create,delete --format '%w%f' "$WATCH_DIR" | while read -r file; do
    
    # 変更があった旨を表示
    echo "[Detected] Change in: $file"
    
    # 更新スクリプト実行
    $UPDATE_SCRIPT
    
    # 連続更新を防ぐための短い待機（0.1秒）
    # git checkoutなどで大量にファイルが変わった時に連打されるのを防ぐ簡易的な措置
    sleep 0.1
    
done