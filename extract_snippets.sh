#!/bin/bash

# 設定
INPUT_FILE="./.vscode/cpp.code-snippets"
OUTPUT_DIR="./snippets/old"

# 必要なコマンドの確認
if ! command -v jq &> /dev/null; then
    echo "Error: jq is required."
    exit 1
fi

# 入力ファイルの存在確認
if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: $INPUT_FILE not found."
    exit 1
fi

# 出力先ディレクトリの作成
mkdir -p "$OUTPUT_DIR"

echo "Extracting snippets from $INPUT_FILE to $OUTPUT_DIR ..."

# jq処理の流れ:
# 1. to_entries: JSONを {key: "name", value: {prefix:..., body:...}} の配列に変換
# 2. prefixの処理: 配列の場合(例: ["rep", "for"])は先頭を使う、文字列ならそのまま
# 3. bodyの処理: 配列の場合は改行で結合、文字列ならそのまま
# 4. @base64: bodyをBase64エンコード（改行や特殊文字を安全にパイプで渡すため）
# 5. 出力: "prefix body(Base64)" という1行の文字列にする

jq -r 'to_entries[] | 
    (.value.prefix | if type=="array" then .[0] else . end) + " " + 
    (.value.body | if type=="array" then join("\n") else . end | @base64)' \
    "$INPUT_FILE" | while read -r prefix b64body; do
    
    # ファイル名の決定
    # prefixにスラッシュが含まれる場合（例: graph/bfs）ディレクトリ階層として扱う
    target_file="$OUTPUT_DIR/${prefix}.cpp"
    target_dir=$(dirname "$target_file")
    
    # ディレクトリ作成
    mkdir -p "$target_dir"

    # Base64をデコードしてファイルに書き出し
    # Linux系は -d, Mac系は -D だが、多くの環境で通るよう --decode を試み、だめなら -D (Mac)
    if echo "$b64body" | base64 --decode > "$target_file" 2>/dev/null; then
        : # Success (GNU/Linux)
    else
        echo "$b64body" | base64 -D > "$target_file" # Fallback for Mac
    fi

    echo "Saved: $target_file"

done

echo "Extraction complete."