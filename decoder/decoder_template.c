#include <decoder.h>

unsigned long state = 0;

int get_hoffman_char(int input, char* ch)
{
  int sent_char = 0;

  switch(state)
  {
?
    default:
      printf("went to default!!\n");
      state = 0;
      return 0;
  }
  return sent_char;
}