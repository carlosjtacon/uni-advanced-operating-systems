#include "count_M.h"

int CountCharacters (int fd, char character)
{
	int n = 0;
	char *input = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);

	int i;
	for (i = 0; i < strlen(input); i++)
	{
		if (input[i]==character)
			n++;
	}

	munmap(input, sizeof(input));
	return n;
}