#include <decoder.h>

state_hoffman_t state = E0;

int __attribute__ ((noinline)) get_hoffman_char(int input, char* ch)
{
  int sent_char = 0;

  switch(state)
  {
		case E0:
			if(input == 0)
			{
				state = E2709232176;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '0';
				sent_char = 1;

				break;
			}
		case E2709232176:
			if(input == 0)
			{
			state = E0;
				*ch = ' ';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E2709232144;
				sent_char = 0;
				break;
			}
		case E2709232144:
			if(input == 0)
			{
				state = E2709232112;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '#';
				sent_char = 1;

				break;
			}
		case E2709232112:
			if(input == 0)
			{
			state = E0;
				*ch = '\n';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '*';
				sent_char = 1;

				break;
			}

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