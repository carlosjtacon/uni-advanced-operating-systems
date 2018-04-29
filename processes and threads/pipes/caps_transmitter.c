#include "caps_transmitter.h"

int caps(int readend, int writeend, char *id)		//conversion to caps
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

		printf("\tTx_%s: transmitting %zu bytes\n",id , strlen(buff));
		if (write(writeend, buff, 1+strlen(buff)) < 0)
			break;
	}

	perror("caps");		//error! aborted from the loop
	return -1;			//print error msg and exit
}