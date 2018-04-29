#include "handling_functions.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int demux(int readCapsA, int readCapsB1, int writeIO);

int main(int argc, char const *argv[])
{
	int readCapsA, readCapsB1, writeIO, r;

	readCapsA = open(argv[1], O_RDONLY);
	readCapsB1 = open(argv[2], O_RDONLY);
	writeIO = open(argv[3], O_WRONLY);

	r = demux(readCapsA, readCapsB1, writeIO);

	close(readCapsA);
	close(readCapsB1);

	return r;
}

int demux(int readCapsA, int readCapsB1, int writeIO)
{
	char all[SIZE], half1[SIZE_HALF], half2[SIZE_HALF];
	int r1, r2;

	for(;;)
	{
		r1 = read(readCapsA, half1, SIZE_HALF);
		r2 = read(readCapsB1, half2, SIZE_HALF);
		
		if (r1 < 0 || r2 < 0)
			break;
		else if(r1 == 0 || r2 == 0)
		{
			close(writeIO);
			return 0;
		}

		concatenate(all, half1, half2);

		printf("\tDemux: rejoining %zu + %zu bytes\n", strlen(half1), strlen(half2));
		if(write(writeIO, all, SIZE) < 0)
			break;
	}

	perror("demux");
	return -1;
}