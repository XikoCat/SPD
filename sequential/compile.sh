#!/bin/sh
rm a.out
echo --- compiling ---
gcc -Wall -std=c99 -lm main.c
echo --- finished ----