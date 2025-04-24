#!/bin/bash
rm encoder
gcc -o encoder main.c huffman.c -I ./ -I lib/include
./encoder