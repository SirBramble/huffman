#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#include <decoder.h>
#include <encoded.h>

int main(void)
{

  for(int i = 0; i < SIZE_ENCODED; i++)
  {
    for(int n = 0; n < 8; n++)
    {
      char ch;
      //printf("%c, %d, %u\t\t\t\t", ch,n,state);
      if(((i*8)+n) > SIZE_HUFFMAN-1) break;
      int bit = (encoded_text[i] & (1 << n)) ? 1 : 0;
      int ret = get_hoffman_char(bit, &ch);
      if(ret)
      {
        //printf("%c, %d, %d, %u, %d\n", ch?ch:' ', bit, n, state, ret);
        printf("%c", ch?ch:' ');
        //get_hoffman_char(encoded[i] & (1 << n) ? 1 : 0, &ch);
      }
    }
  }
  printf("\n");
  return 0;
}