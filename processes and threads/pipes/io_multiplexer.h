#ifndef _IO_MULTIPLEXER_
#define _IO_MULTIPLEXER_

#include "handling_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int io(int readend, int writeA, int writeB);
int mux(char all[SIZE], int writeCapsA, int writeCapsB1);

#endif