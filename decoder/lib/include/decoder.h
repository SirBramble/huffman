#ifndef _DECODER_TEMPLATE_H_
#define _DECODER_TEMPLATE_H_

#include <stdint.h>
#include <encoded.h>

#pragma "included decoder_template"

int __attribute__ ((noinline)) get_hoffman_char(int input, char* ch);
void print_logo_hoffman(uint32_t* handle, void (*uart_put_char_func)(uint32_t* handle, char c));

typedef enum
{
  E0,
	E507730480,
	E507730448,
	E507730416
}state_hoffman_t;

extern state_hoffman_t state;

#endif // _DECODER_TEMPLATE_H_