#ifndef _DECODER_TEMPLATE_H_
#define _DECODER_TEMPLATE_H_

#include <stdint.h>
#include <encoded_text.h>

#pragma "included decoder_template"

#define ENCODED_BIT_LIMIT 16

int __attribute__ ((noinline)) get_hoffman_char(int input, char* ch);

typedef enum
{
  E0,
	E94822513171680,
	E94822513171648,
	E94822513171616,
	E94822513171552,
	E94822513171456,
	E94822513171360,
	E94822513171584,
	E94822513171488,
	E94822513171392,
	E94822513171520,
	E94822513171424,
	E94822513171328
}state_hoffman_t;

extern state_hoffman_t state;

#endif // _DECODER_TEMPLATE_H_