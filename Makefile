# Repository directory path (can be overwritten by other makefile)
HUFFMAN_HOME ?= $(CURDIR)

# Path to File
TEXT_FILE ?= "$(HUFFMAN_HOME)/example_text/text.txt"

# Array configuration
# Valid options: ENCODE_UINT8, ENCODE_UINT16, ENCODE_UINT32
TYPE_DEFINE ?= ENCODE_UINT16

1_huffman_gen: huffman_gen_build
	@cd $(HUFFMAN_HOME)/huffman_gen && chmod +x ./build/encoder
	cd $(HUFFMAN_HOME)/huffman_gen && ./build/encoder $(TEXT_FILE)

huffman_gen_build:
	gcc -D $(TYPE_DEFINE) $(HUFFMAN_HOME)/huffman_gen/main.c $(HUFFMAN_HOME)/huffman_gen/huffman.c -I $(HUFFMAN_HOME)/huffman_gen -o $(HUFFMAN_HOME)/huffman_gen/build/encoder

2_decoder: decoder_build
	@cd $(HUFFMAN_HOME)/decoder && chmod +x ./build/decoder
	cd $(HUFFMAN_HOME)/decoder && ./build/decoder

decoder_build: 1_huffman_gen
	@cp $(HUFFMAN_HOME)/lib/include/encoded_text.h $(HUFFMAN_HOME)/decoder/lib/include
	@cp $(HUFFMAN_HOME)/lib/source/encoded_text.c $(HUFFMAN_HOME)/decoder/lib/source
	@cp $(HUFFMAN_HOME)/lib/include/huffman_decoder.h $(HUFFMAN_HOME)/decoder/lib/include
	@cp $(HUFFMAN_HOME)/lib/source/huffman_decoder.c $(HUFFMAN_HOME)/decoder/lib/source
	gcc $(HUFFMAN_HOME)/decoder/lib/source/huffman_decoder.c $(HUFFMAN_HOME)/decoder/lib/source/encoded_text.c $(HUFFMAN_HOME)/decoder/main.c -I $(HUFFMAN_HOME)/decoder/lib/include -o $(HUFFMAN_HOME)/decoder/build/decoder

clean:
#clean decoder stage
	@rm -f $(HUFFMAN_HOME)/decoder/lib/source/*
	@rm -f $(HUFFMAN_HOME)/decoder/lib/include/*
	@rm -f $(HUFFMAN_HOME)/decoder/build/*
#clean huffman_gen stage
	@rm -f $(HUFFMAN_HOME)/huffman_gen/build/*
#clean output lib stage
	@rm -f $(HUFFMAN_HOME)/lib/include/*
	@rm -f $(HUFFMAN_HOME)/lib/source/*

# Clean for external calls
clean_huffman:
#clean decoder stage
	@rm -f $(HUFFMAN_HOME)/decoder/lib/source/*
	@rm -f $(HUFFMAN_HOME)/decoder/lib/include/*
	@rm -f $(HUFFMAN_HOME)/decoder/build/*
#clean huffman_gen stage
	@rm -f $(HUFFMAN_HOME)/huffman_gen/build/*
#clean output lib stage
	@rm -f $(HUFFMAN_HOME)/lib/include/*
	@rm -f $(HUFFMAN_HOME)/lib/source/*
