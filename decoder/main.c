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
      //if(((i*8)+n) > SIZE_HUFFMAN+1) break;
      if(get_hoffman_char(encoded[i] & (1 << n) ? 1 : 0, &ch) != 0)
      {
        printf("%c, %d, %u\n", ch,n,state);
        printf("\n");
        get_hoffman_char(encoded[i] & (1 << n) ? 1 : 0, &ch);
      }
    }
  }
  return 0;
}