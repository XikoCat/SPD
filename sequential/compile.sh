#!/bin/sh
rm a.out
echo --- compiling ---
gcc -Wall -std=c99 -lm -g -fsanitize=address main.c
echo --- finished ----