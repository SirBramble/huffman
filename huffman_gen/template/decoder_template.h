#ifndef _DECODER_TEMPLATE_H_
#define _DECODER_TEMPLATE_H_

#include <stdint.h>
#include <encoded_text.h>

#pragma "included decoder_template"

?

int __attribute__ ((noinline)) get_hoffman_char(int input, char* ch);

typedef enum
{
  E0,
?
}state_hoffman_t;

extern state_hoffman_t state;

#endif // _DECODER_TEMPLATE_H_