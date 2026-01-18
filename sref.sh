#!/bin/bash

# 設定
SRC_DIR="./snippets"
OUT_FILE="./.vscode/snip.code-snippets"

# jqコマンドの存在確認
if ! command -v jq &> /dev/null; then
    echo "Error: jq command not found. Please install jq."
    exit 1
fi

# 出力先ディレクトリの作成
mkdir -p "$(dirname "$OUT_FILE")"

echo "Generating snippets from $SRC_DIR to $OUT_FILE ..."

# ./snippets 配下のファイルを再帰的に検索し、ループ処理
find "$SRC_DIR" -type f -name "*.cpp" | while read -r filepath; do
    
    # 1. パスとファイル名の加工
    # 例: ./snippets/graph/dijkstra.cpp -> graph/dijkstra.cpp
    relpath="${filepath#$SRC_DIR/}"
    
    # 拡張子を削除 (graph/dijkstra)
    noext="${relpath%.*}"
    
    # スニペット名: スラッシュをドットに置換 (graph.dijkstra)
    snip_name="${noext//\//.}"
    
    # Prefix: ファイル名部分のみ抽出 (dijkstra)
    snip_prefix=$(basename "$noext")
    
    # 2. 本文(body)の読み込みとJSON配列化
    # jq -R -s: ファイル全体を生テキストとして読み込む
    # split("\n"): 改行で分割して配列にする
    body=$(jq -R -s 'split("\n")' < "$filepath")

    # 3. 単体スニペットのJSONオブジェクト生成
    # --arg でシェル変数をjq内の変数に渡す
    jq -n \
       --arg name "$snip_name" \
       --arg prefix "$snip_prefix" \
       --argjson body "$body" \
       '{ ($name): { "prefix": $prefix, "body": $body, "description": $name, "scope": "cpp" } }'

done | jq -s 'add' > "$OUT_FILE" # 4. 全てのJSONオブジェクトを結合してファイルに書き出し

echo "Done! Created snippets with $(jq 'length' "$OUT_FILE") entries."