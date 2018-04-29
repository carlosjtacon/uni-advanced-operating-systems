#include <string.h>
#include <fcntl.h>

#include "readchar_R.h"
#include "count_M.h"

int main(int argc, char const *argv[])
{
	const char *HELP = "Usage: ./count [parameter] [file] [character]\nWhere: parameter is one of:\n\t\tR - for counting while reading with read().\n\t\tM - for counting with memory-mapping.\nFile is the file name in folder.\nCharacter is only one char.";
	
	int fd, count;

	if (argc == 4)
	{
		if (strcmp(argv[1],"R")==0)
		{
			if ((fd = open(argv[2], O_RDONLY))>=0)
			{
				if(strlen(argv[3])==1)
				{
					count = 0;
					int i;
					for (i = 0; i < lseek(fd, 0, SEEK_END); i++)
					{
						if (ReadCharacter(fd,i) == *argv[3])
						{
							count++;
						}
					}
					printf("%d\n", count);
				}
				else
					printf("Third argument must be only one character.\n");
				close(fd);
			}
			else
				printf("File not found %s\n", argv[2]);
		}
		else if (strcmp(argv[1],"M")==0)
		{
			if ((fd = open(argv[2], O_RDONLY))>=0)
			{
				if(strlen(argv[3])==1)
				{
					count = CountCharacters(fd, *argv[3]);
					printf("%d\n", count);
				}
				else
					printf("Third argument must be only one character.\n");
				close(fd);
			}
			else
				printf("File not found %s\n", argv[2]);
		}
		else
			printf("%s not found\n", argv[1]);
	} 
	else
		printf("%s\n", HELP);
	return 0;
}