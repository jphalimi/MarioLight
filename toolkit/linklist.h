//
//  linklist.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_LINKLIST
#define H_LINKLIST

/* Typedefs */
typedef void (*linkList_fct) (void *data);

typedef struct sLinkListNode {
    void *data;
    struct sLinkListNode *next;
} SLinkListNode;

typedef struct sLinkList {
    SLinkListNode *head;
    linkList_fct print;
    linkList_fct destroy;
} SLinkList;

/* Functions signatures */
SLinkList *LinkList_create (const linkList_fct print, const linkList_fct destroy);
void LinkList_add (SLinkList *ll, void *data);
void *LinkList_getElementAt (const SLinkList *ll, unsigned idX);
unsigned LinkList_getSize (const SLinkList *ll);
void LinkList_print (const SLinkList *ll);
void LinkList_destroy (SLinkList *ll);

SLinkListNode *LinkListNode_init (void *data, SLinkListNode *next);
SLinkListNode *LinkListNode_destroy (SLinkListNode *lln, const linkList_fct destroy);

#endif