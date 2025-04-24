#!/bin/bash
rm decoder
gcc -o decoder main.c lib/source/decoder.c ../huffman_gen/lib/source/encoded.c -I lib/include -I ../huffman_gen/lib/include
./decoder