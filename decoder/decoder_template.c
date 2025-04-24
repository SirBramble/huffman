#include <decoder.h>

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

void print_logo_hoffman(uint32_t* handle, void (*uart_put_char_func)(uint32_t* handle, char c))
{
  {
    for(int i = 0; i < SIZE_ENCODED; i++)
    {
      for(int n = 0; n < 8; n++)
      {
        char ch;
        if(((i*8)+n) > SIZE_HUFFMAN-1) break;
        int bit = (encoded_text[i] & (1 << n)) ? 1 : 0;
        int ret = get_hoffman_char((int)bit, &ch);
        if(ret)
        {
          uart_put_char_func(handle, ch);
        }
      }
    }
  }
}