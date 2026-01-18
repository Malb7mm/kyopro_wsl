#!/bin/bash
if [[ "$1" == *"/"* ]]; then
    DIR=${1%/*}
    mkdir -p "./saved/$DIR"
fi
FILE_PATH="./saved/${1}.cpp"
cp -r ./main.cpp "$FILE_PATH"