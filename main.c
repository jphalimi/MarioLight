//
//  main.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "toolkit/linklist.h"

void printer (void *data) {
	int value = *((int*)data);
	
	printf("Value : %d\n", value);
}

int main (int argc, char *argv[])
{
	int tab[5] = {909051, 1998, 4519, 8591, 1949};
	SLinkList *new = LinkList_create(printer, NULL);
	int *value;
	
	LinkList_add(new, tab);
	LinkList_add(new, tab+1);
	LinkList_add(new, tab+2);
	LinkList_add(new, tab+3);
	LinkList_add(new, tab+4);
	
	LinkList_print(new);
	
	value = LinkList_getElementAt(new, 4);
	
	if (value != NULL) {
		fprintf(stderr, "LinkList size = %d\n", *value);
	} else {
		fprintf(stderr, "LinkList size is invalid\n");
		return EXIT_FAILURE;
	}
	
	LinkList_destroy(new);
	
	(void) argc;
	(void) argv;
	return EXIT_SUCCESS;
}

