//
//  log.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_LOG
#define H_LOG

#include <stdio.h>

typedef struct sLog {
    FILE *fd;
    int verbosity;
} SLog;

void Log_setOutput (FILE *fd);
void Log_setVerbosity (int verbosity);
int Log_output (int verbosity, const char *fmt, ...);
int Log_flush ();

#endif