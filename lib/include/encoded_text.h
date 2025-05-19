#ifndef _ENCODED_TEMPLATE_H
#define _ENCODED_TEMPLATE_H

#include <stdint.h>

#define ENCODE_TYPE uint16_t

#pragma "included encoded_template"

#define SIZE_ENCODED 514        
#define SIZE_HUFFMAN 8222          

extern ENCODE_TYPE encoded_text[SIZE_ENCODED];

#endif // _ENCODED_TEMPLATE_H