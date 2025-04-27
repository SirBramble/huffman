# Huffman Text Encoder/Decoder
When working with text on microcontrollers or other embedded devices, storage usually comes at a premium. Especially larger splash screens or help pages can take up a lot of space. This project aims to solve this problem by compressing the text with huffman encoding.
The `huffman_gen` takes a input file and generates a encoded version of the text, as well as a state maschine decoder that can be included in a project.
The `decoder` in `./decoder` is a example implementation.

## How to use
1. Edit the `TEXT_FILE` Variable in the `Makefile` to point to your desired text file.
2. Run `make clean 2_decoder`.
3. Copy the resulting files from `./lib` into your project or reference/include them.
4. See `./decoder/main.c` for an example implementation.