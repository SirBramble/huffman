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
				state = E94822513171680;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = ' ';
				sent_char = 1;

				break;
			}
		case E94822513171680:
			if(input == 0)
			{
			state = E0;
				*ch = '%';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E94822513171648;
				sent_char = 0;
				break;
			}
		case E94822513171648:
			if(input == 0)
			{
				state = E94822513171616;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '8';
				sent_char = 1;

				break;
			}
		case E94822513171616:
			if(input == 0)
			{
				state = E94822513171552;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E94822513171584;
				sent_char = 0;
				break;
			}
		case E94822513171552:
			if(input == 0)
			{
			state = E0;
				*ch = '"';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E94822513171456;
				sent_char = 0;
				break;
			}
		case E94822513171456:
			if(input == 0)
			{
			state = E0;
				*ch = 'b';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E94822513171360;
				sent_char = 0;
				break;
			}
		case E94822513171360:
			if(input == 0)
			{
			state = E0;
				*ch = ',';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = 'Y';
				sent_char = 1;

				break;
			}
		case E94822513171584:
			if(input == 0)
			{
				state = E94822513171488;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E94822513171520;
				sent_char = 0;
				break;
			}
		case E94822513171488:
			if(input == 0)
			{
			state = E0;
				*ch = '\n';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E94822513171392;
				sent_char = 0;
				break;
			}
		case E94822513171392:
			if(input == 0)
			{
			state = E0;
				*ch = '\'';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = '`';
				sent_char = 1;

				break;
			}
		case E94822513171520:
			if(input == 0)
			{
				state = E94822513171424;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = 'a';
				sent_char = 1;

				break;
			}
		case E94822513171424:
			if(input == 0)
			{
				state = E94822513171328;
				sent_char = 0;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = 'd';
				sent_char = 1;

				break;
			}
		case E94822513171328:
			if(input == 0)
			{
			state = E0;
				*ch = '.';

			sent_char = 1;
				break;
			}
			if(input != 0)
			{
				state = E0;
				*ch = 'P';
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