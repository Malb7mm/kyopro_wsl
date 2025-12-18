#!/bin/bash
DIR=$(echo "$1" | sed -E "s/(.*)\\/.*?/\\1/")
mkdir -p ./saved/$DIR
cp -r ./main.cpp ./saved/${1}.cpp