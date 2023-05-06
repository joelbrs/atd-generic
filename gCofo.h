#ifndef __COFO_H
#define __COFO_H

typedef struct _cofo_ gCofo;

gCofo *gCofCreate(int maxItems);

int gCofInsert(gCofo *c, void *item);

int gCofEmptyDestroy(gCofo *c);

int gCofClearAll(gCofo *c);

void *gcofQuery(gCofo *c, void *key, int (*cmp)(void *, void *));

void *gcofRemove(gCofo *c, void *key, int (*cmp)(void *, void *));

void *gcofGetFirst(gCofo *c);

void *gcofGetNext(gCofo *c);

#endif