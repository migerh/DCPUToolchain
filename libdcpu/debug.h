/**

	File:		debug.h

	Project:	DCPU-16 Toolchain
	Component:	LibDCPU

	Authors:	James Rhodes

	Description:	Declares functions for logging and determining
			the level of logging appropriate.

**/

#ifndef __DCPU_DEBUG_H
#define __DCPU_DEBUG_H

#include <stdio.h>
#include "dcpu.h"
#include "bstring.h"

#define LEVEL_EVERYTHING 6
#define LEVEL_DEBUG 5
#define LEVEL_VERBOSE 4
#define LEVEL_DEFAULT 3
#define LEVEL_ERROR 2
#define LEVEL_CRITICAL 1
#define LEVEL_SILENT 0

void printd(int level, const char* message, ...);
void debug_setlevel(int level);
int debug_getlevel();

#endif
