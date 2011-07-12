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
	SDL_Surface *screen;
	
	SDL_Init (SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	if (screen == NULL) {
		fprintf(stderr, "Error\n");
		exit (EXIT_FAILURE);
	}
	
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
	
	SDL_Flip( screen );
	SDL_Delay( 2000 );
	
	LinkList_destroy(new);
	
	SDL_Quit ();
	
	(void) argc;
	(void) argv;
	return EXIT_SUCCESS;
}

