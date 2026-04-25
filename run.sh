#!/bin/bash
MODE_VAL=0
EXTRA_FLAGS=""
for arg in "$@"; do
  case $arg in
    0|1|2|3|4)
      MODE_VAL=$arg
      ;;
    -1)
      MODE_VAL=-1
      ;;
    -2)
      MODE_VAL=-2
      ;;
    -e)
      EXTRA_FLAGS="$EXTRA_FLAGS -DSHOW_CERR"
      ;;
    -t)
      EXTRA_FLAGS="$EXTRA_FLAGS -DSHOW_EVERY_TESTCASES"
      ;;
  esac
done
g++ main.cpp -std=gnu++23 -O2 -DLOCAL -DATCODER -DMODE=$MODE_VAL $EXTRA_FLAGS -o main
echo "Compile finished. (MODE: $MODE_VAL)" >&2
./main