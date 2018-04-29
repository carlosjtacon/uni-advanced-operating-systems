#ifndef _COUNT_M_
#define _COUNT_M_ 

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>

int CountCharacters (int fd, char character);

#endif