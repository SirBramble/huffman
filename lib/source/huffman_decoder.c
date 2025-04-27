#include <huffman_decoder.h>

state_hoffman_t state = E0;

int __attribute__ ((noinline)) get_hoffman_char(int input, char* ch)
{
  int sent_char = 0;

  switch(state)
  {
		case E0:
			if(input == 0)
			{
			state = E0;
				*ch = ' ';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E94617712097920;
				sent_char = 0;
				break;
			}
		case E94617712097920:
			if(input == 0)
			{
			state = E0;
				*ch = '\\';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E94617712097888;
				sent_char = 0;
				break;
			}
		case E94617712097888:
			if(input == 0)
			{
				state = E94617712097856;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '_';
				sent_char = 1;

				break;
			}
		case E94617712097856:
			if(input == 0)
			{
				state = E94617712097824;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '|';
				sent_char = 1;

				break;
			}
		case E94617712097824:
			if(input == 0)
			{
			state = E0;
				*ch = '/';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '\n';
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