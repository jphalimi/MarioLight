//
//  main.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "toolkit/linklist.h"
#include "toolkit/log.h"
#include "game/config/config.h"

void printer (void *data) {
	int value = *((int*)data);
	
	Log_output(1, "Value : %d\n", value);
}

int main (int argc, char *argv[])
{
	int tab[5] = {909051, 1998, 4519, 8591, 1949};
	SLinkList *new = LinkList_create(printer, NULL);
	int *value;
	
	Log_setOutput(stderr);
	Log_setVerbosity(3);
	
	SConfig *config = Config_create();
	
	LinkList_add(new, tab);
	LinkList_add(new, tab+1);
	LinkList_add(new, tab+2);
	LinkList_add(new, tab+3);
	LinkList_add(new, tab+4);
	
	LinkList_print(new);
	
	value = LinkList_getElementAt(new, 4);
	
	if (value != NULL) {
		Log_output(-1, "LinkList element at 4 = %d\n", *value);
	} else {
		Log_output (-1, "LinkList size is invalid\n");
		return EXIT_FAILURE;
	}
	
	Log_output(2, "Test with verbosity = 2\n");
	Log_output(4, "Test with verbosity = 4\n");
	fprintf(stderr, "Test value : %d\n", 89);
	Log_output(1, "Test value : %d\n", 89);
	
	Log_output(1, "Game name : %s\n", Config_getGameName(config));
	Log_output(1, "Game window width : %u\n", Config_getWindowWidth(config));
	Log_output(1, "Game window height : %u\n", Config_getWindowHeight(config));
	
	Config_destroy(config);
	
	LinkList_destroy(new);
	
	(void) argc;
	(void) argv;
	return EXIT_SUCCESS;
}

