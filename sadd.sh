#!/bin/bash
if [[ "$1" == *"/"* ]]; then
    DIR=${1%/*}
    mkdir -p "./snippets/$DIR"
fi
FILE_PATH="./snippets/${1}.cpp"
touch "$FILE_PATH"
code -r "$FILE_PATH"