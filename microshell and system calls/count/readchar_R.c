#include "readchar_R.h"

char ReadCharacter (int fd, int position)
{
	char c;
	lseek(fd, position, SEEK_SET);
	read(fd, &c, 1);
	return c;
}