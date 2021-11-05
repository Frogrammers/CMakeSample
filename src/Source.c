#include "Header.h"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		return -1;
	}
	char * msg = argv[1];
	
	print_message(msg);

	return 0;
}
