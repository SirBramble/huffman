#include <decoder.h>

unsigned long state = 0;

int get_hoffman_char(int input, char* ch)
{
  int sent_char = 0;

  switch(state)
  {
		case 0:
			if(input == 0)
			{
				putchar('0');
				state = 1238575568;
				break;
				sent_char = 0;
			}
			if(input != 0)
			{
				putchar('1');
				state = 1238575600;
				break;
				sent_char = 0;
			}
		case 1238575568:
			if(input == 0)
			{
				putchar('0');
				state = 1238575440;
				break;
				sent_char = 0;
			}
			if(input != 0)
			{
				putchar('1');
				state = 1238575536;
				break;
				sent_char = 0;
			}
		case 1238575440:
			state = 0;
			*ch = '*';
			sent_char = 1;
			break;
		case 1238575536:
			state = 0;
			*ch = 'g';
			sent_char = 1;
			break;
		case 1238575600:
			if(input == 0)
			{
				putchar('0');
				state = 1238575504;
				break;
				sent_char = 0;
			}
			if(input != 0)
			{
				putchar('1');
				state = 1238575472;
				break;
				sent_char = 0;
			}
		case 1238575504:
			state = 0;
			*ch = '-';
			sent_char = 1;
			break;
		case 1238575472:
			state = 0;
			*ch = '+';
			sent_char = 1;
			break;

    default:
      printf("went to default!!\n");
      state = 0;
      return 0;
  }
  return sent_char;
}