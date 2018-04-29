#ifndef _DEMULTIPLEXER_
#define _DEMULTIPLEXER_

#include "handling_functions.h"
#include <unistd.h>
#include <stdio.h>

int demux(int readCapsA, int readCapsB1, int writeIO);

#endif