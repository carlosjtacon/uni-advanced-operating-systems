#include "io_multiplexer.h"

int io(int readend, int writeA, int writeB)		//input / output
{
	int r;
	char buff[SIZE];
	printf("Type lines of text(Control+D to finish):\n");

	for (;;)	//(Almost) infinite loop
	{

		if (fgets(buff, SIZE, stdin))	//reads from keyboard
		{
			if (mux(buff, writeA, writeB) < 0)
				break;
		}						//If read, send (if error while sending abort)
		else					//If EOF, close pipes
		{
			close(writeA);
			close(writeB);
			return 0;
		}
		
		r = read(readend, buff, SIZE);	//wait pipe response
		
		if (r < 0)	//if error abort
			break;

		fputs(buff, stdout);	//show what the child process returned and repeat
	}

	perror("io");	//error! aborted from the loop
	return -1;		//exit
}

int mux(char all[SIZE], int writeCapsA, int writeCapsB1)
{
	char half1[SIZE_HALF], half2[SIZE_HALF];
	int w1, w2;

	printf("\tMux: separating %zu bytes\n", strlen(all));
	split(all, half1, half2);
	
	w1 = write(writeCapsA, half1, 1+strlen(half1));
	w2 = write(writeCapsB1, half2, 1+strlen(half2));
	
	if(w1 < 0 || w2 < 0)
	{
		perror("mux");
		return -1;
	}

	return 0;
}