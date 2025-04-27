#include <huffman_decoder.h>

state_hoffman_t state = E0;

int __attribute__ ((noinline)) get_hoffman_char(int input, char* ch)
{
  int sent_char = 0;

  switch(state)
  {
?
    default:
      state = 0;
      return 0;
      break;
  }
  return sent_char;
}