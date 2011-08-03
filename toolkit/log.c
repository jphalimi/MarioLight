//
//  log.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include "log.h"

static SLog m_log = {
	.fd = NULL,
    .verbosity = 0
};

void Log_setOutput (FILE *fd) {
    m_log.fd = fd;
}

void Log_setVerbosity (int verbosity) {
    m_log.verbosity = verbosity;
}

int Log_output (int verbosity, const char *fmt, ...) {
    va_list va;
    int res;
    
    if (verbosity > m_log.verbosity) {
        return -1;
    }
    
    va_start(va, fmt);
    /* va_arg() is going to call the argument followed by fmt */
    res = vfprintf(m_log.fd, fmt, va);
    va_end(va);
    
    return res;
}