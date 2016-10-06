#include <stdio.h>
#include <stdlib.h>
#include "bubble.h"

node_t *sort( node_t *start )
{
    if( start == NULL ) return NULL;
    start->next = sort(start->next);
    if( start->next != NULL && start->data > start->next->data ) {
        start = move( start );
    }
    return start;
}

node_t *move( node_t *x )
{
    node_t *n, *p, *ret;

    p = x;
    n = x->next;
    ret = n;
    while( n != NULL && x->data > n->data ) {
        p = n;
        n =  n->next;
    }
    /* we now move the top item between p and n */
    p->next = x;
    x->next = n;
    return ret;
}
