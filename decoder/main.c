#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#include <huffman_decoder.h>
#include <encoded_text.h>

void print_text_hoffman()
{
  for(int i = 0; i < SIZE_ENCODED; i++)
  {
    for(int n = 0; n < ENCODED_BIT_LIMIT; n++)
    {
      char ch;
      if(((i*ENCODED_BIT_LIMIT)+n) > SIZE_HUFFMAN-1) break;
      int bit = (encoded_text[i] & (1 << n)) ? 1 : 0;
      int ret = get_hoffman_char((int)bit, &ch);
      if(ret)
      {
        putchar(ch);
      }
    }
  }
}

int main(void)
{

  print_text_hoffman();
  putchar('\n');
  return 0;
}