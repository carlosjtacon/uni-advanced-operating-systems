#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define SIZE 100

int caps(int readend, int writeend, const char *id);

int main(int argc, char const *argv[])
{
	int readend, writeend, r;
	const char *id;

	readend = open(argv[1], O_RDONLY);
	writeend = open(argv[2], O_WRONLY);
	id = argv[3];

	r = caps(readend, writeend, id);

	close(readend);

	return r;
}

int caps(int readend, int writeend, const char *id)		//conversion to caps
{
	int i, r;
	char buff[SIZE];

	srand((unsigned)getpid() ^ (unsigned)time(NULL));

	for(;;)	//(Almost) infinite loop
	{
		r = read(readend, buff, SIZE);	//receive string
		
		if (r < 0)	//if error abort
			break;
		else if (r == 0)	//if pipe was closed close the other one and finish ok
		{
			close(writeend);
			return 0;
		}				//convert some letters to capitals (with prob 0.5)

		for (i = 0; buff[i]; i++)
			if (rand() > RAND_MAX/2)
				if (buff[i]>= 'a' && buff[i]<='z')
					buff[i]-=('a' - 'A');
							//send back

		if (id)
			printf("\tTx_%s: transmitting %zu bytes\n",id , strlen(buff));
		else
			printf("\tTx: transmitting %zu bytes\n", strlen(buff));

		if (write(writeend, buff, 1+strlen(buff)) < 0)
			break;
	}

	perror("caps");		//error! aborted from the loop
	return -1;			//print error msg and exit
}