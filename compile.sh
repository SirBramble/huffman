#!/bin/bash

#clean decoder stage
rm decoder/lib/source/*
rm decoder/lib/include/*

#clean huffman_gen stage
rm huffman_gen/lib/source/*
rm huffman_gen/lib/include/*

cd ./huffman_gen/
./compile.sh
cd ../decoder
./compile.sh

cd ..
cp ./huffman_gen/lib/source/* ./lib/source
cp ./huffman_gen/lib/include/* ./lib/include
cp ./decoder/lib/source/* ./lib/source
cp ./decoder/lib/include/* ./lib/include