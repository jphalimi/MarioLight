//
//  linklist.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linklist.h"

inline SLinkListNode *LinkListNode_create (void *data, SLinkListNode *next) {
    SLinkListNode *lln = malloc (sizeof(*lln));
    assert (lln != NULL);
    memset(lln, 0, sizeof(*lln));
    
    lln->data = data;
    lln->next = next;
    
    return lln;
}

inline SLinkListNode *LinkListNode_destroy (SLinkListNode *lln, const linkList_fct destroy) {
    SLinkListNode *next = NULL;
    
    if (lln != NULL) {
        if (destroy != NULL) {
            destroy (lln->data);
        }
        next = lln->next;
        free(lln), lln = NULL;
    }
    
    return next;
}

SLinkList *LinkList_create (const linkList_fct print, const linkList_fct destroy) {
    SLinkList *ll = malloc (sizeof(*ll));
    assert (ll != NULL);
    memset(ll, 0, sizeof(*ll));
    
    ll->head = NULL;
    ll->print = print;
    ll->destroy = destroy;
    
    return ll;
}

void LinkList_add (SLinkList *ll, void *data) {
    if (ll != NULL && data != NULL) {
        SLinkListNode *new = LinkListNode_create (data, ll->head);
        ll->head = new;
    }
}

void *LinkList_getElementAt (const SLinkList *ll, unsigned idX) {
    unsigned i;
    
    if (ll != NULL) {
        SLinkListNode *tmp = ll->head;
        if (tmp == NULL) { /* In case of empty list */
            return NULL;
        }
        for (i = 0; i < idX; i++) {
            tmp = tmp->next;
            /* If tmp == NULL, then it's because we didn't reach our idX yet
             and the linkList is already finished */
            if (tmp == NULL) {
                return NULL;
            }
        }
        return tmp->data;
    }
    
    return NULL;
}

unsigned LinkList_getSize (const SLinkList *ll) {
    unsigned size = 0;
    SLinkListNode *tmp;
    
    if (ll != NULL) {
        tmp = ll->head;
        while (tmp != NULL) {
            tmp = tmp->next;
            size++;
        }
    }
    
    return size;
}

void LinkList_destroy (SLinkList *ll) {
    SLinkListNode *tmp;
    
    if (ll != NULL) {
        tmp = ll->head;
        while (tmp != NULL) {
            tmp = LinkListNode_destroy (tmp, ll->destroy);
        }
    }
    free(ll), ll = NULL;
}

void LinkList_print (const SLinkList *ll) {
    SLinkListNode *tmp;
    
    if (ll != NULL && ll->print != NULL) {
        tmp = ll->head;
        while (tmp != NULL) {
            ll->print (tmp->data);
            tmp = tmp->next;
        }
    }
}