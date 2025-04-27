#ifndef _ENCODED_TEMPLATE_H
#define _ENCODED_TEMPLATE_H

#include <stdint.h>

#define ENCODE_TYPE uint16_t

#pragma "included encoded_template"

#define SIZE_ENCODED 70        
#define SIZE_HUFFMAN 1120          

extern ENCODE_TYPE encoded_text[SIZE_ENCODED];

#endif // _ENCODED_TEMPLATE_H