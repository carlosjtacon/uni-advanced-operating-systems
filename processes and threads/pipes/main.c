#include "io_multiplexer.h"
#include "caps_transmitter.h"
#include "demultiplexer.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ioToCapsA[2], ioToCapsB1[2], capsB1ToCapsB2[2], capsAToDemux[2], capsB2ToDemux[2], back[2], r;  

	if (pipe(ioToCapsA) || pipe(ioToCapsB1) || pipe(capsB1ToCapsB2) || pipe(capsAToDemux) || pipe(capsB2ToDemux) || pipe(back))
	{
		perror("pipe");
		return -1;
	}

	if (fork() == 0)	//child to io
	{
		close(ioToCapsA[0]);
		close(ioToCapsB1[0]);
		close(back[1]);
		r = io(back[0], ioToCapsA[1], ioToCapsB1[1]);
		close(back[0]);
		close(ioToCapsB1[1]);
		close(ioToCapsA[1]);

		return r;
	}

	//parent
	close(ioToCapsB1[1]);	//close writing signal
	close(ioToCapsA[1]);
	
	if(fork() == 0)	//child caps A
	{
		close(ioToCapsA[1]);
		close(capsAToDemux[0]);
		r = caps(ioToCapsA[0], capsAToDemux[1], "A");
		close(ioToCapsA[0]);
		close(capsAToDemux[1]);
		return r;
	}
	
	if (fork() == 0)		//child caps b1
	{
		if (fork() == 0)	//child caps b2
		{
			close(capsB1ToCapsB2[1]);
			close(capsB2ToDemux[0]);
			r = caps(capsB1ToCapsB2[0], capsB2ToDemux[1], "B2");
			close(capsB1ToCapsB2[0]);
			close(capsB2ToDemux[1]);
			return r;
		}

		close(ioToCapsB1[1]);
		close(capsB1ToCapsB2[0]);
		r = caps(ioToCapsB1[0], capsB1ToCapsB2[1], "B1");
		close(ioToCapsB1[0]);
		close(capsB1ToCapsB2[1]);

		wait(NULL);
		return r;
	}
		
	//parent demux
	close(capsB1ToCapsB2[1]);	//close writing signal
	
	close(capsAToDemux[1]);
	close(capsB2ToDemux[1]);
	close(back[0]);
	r = demux(capsAToDemux[0], capsB2ToDemux[0], back[1]);
	close(capsAToDemux[0]);
	close(capsB2ToDemux[0]);
	close(back[1]);
	
	wait(NULL);
	wait(NULL);
	wait(NULL);

	return r;

}