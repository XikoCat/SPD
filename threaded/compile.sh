#!/bin/sh
rm a.out
rm my_utils.h.gch
echo --- compiling ---
gcc -Wall -std=c99 -lm -g -fsanitize=address main.c ./my_utils.h
echo --- finished ----