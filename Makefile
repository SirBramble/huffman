# Path to File (relative to project root)
TEXT_FILE ?= "text.txt"

# Array configuration
# Valid options: ENCODE_UINT8, ENCODE_UINT16, ENCODE_UINT32
TYPE_DEFINE ?= ENCODE_UINT16

1_huffman_gen: huffman_gen_build
	@cd ./huffman_gen && chmod +x ./build/encoder
	cd ./huffman_gen && ./build/encoder "../$(TEXT_FILE)"

huffman_gen_build:
	gcc -D $(TYPE_DEFINE) huffman_gen/main.c huffman_gen/huffman.c -I huffman_gen -o huffman_gen/build/encoder

2_decoder: decoder_build
	@cd ./decoder && chmod +x ./build/decoder
	cd ./decoder && ./build/decoder

decoder_build: 1_huffman_gen
	@cp ./lib/include/encoded_text.h ./decoder/lib/include
	@cp ./lib/source/encoded_text.c ./decoder/lib/source
	@cp ./lib/include/huffman_decoder.h ./decoder/lib/include
	@cp ./lib/source/huffman_decoder.c ./decoder/lib/source
	gcc decoder/lib/source/huffman_decoder.c decoder/lib/source/encoded_text.c decoder/main.c -I decoder/lib/include -o decoder/build/decoder

clean:
#clean decoder stage
	@rm -f decoder/lib/source/*
	@rm -f decoder/lib/include/*
	@rm -f decoder/build/*
#clean huffman_gen stage
	@rm -f huffman_gen/build/*
#clean output lib stage
	@rm -f lib/include/*
	@rm -f lib/source/*