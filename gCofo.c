#include "gCofo.h"
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct _cofo_ {
  int numItens;
  int maxItens;
  int cur;
  void **item;
} gCofo;

gCofo *gCofCreate(int maxItems) {
  gCofo *c;

  if (maxItems > 0) {
    c = (gCofo *)malloc(sizeof(gCofo));

    if (c != NULL) {
      c->item = (void **)malloc(sizeof(void *) * maxItems);
      c->maxItens = maxItems;
      c->numItens = 0;
      c->cur = -1;

      return c;
    }
    free(c);
  }
  return NULL;
}

int gCofInsert(gCofo *c, void *item) {
  if (c != NULL) {
    if (c->numItens < c->maxItens) {
      c->item[c->numItens] = item;
      c->numItens++;
      return TRUE;
    }
  }

  return FALSE;
}

int gCofEmptyDestroy(gCofo *c) {
  if (c != NULL && c->numItens == 0) {
    free(c->item);
    free(c);

    return TRUE;
  }

  return FALSE;
}

int gCofClearAll(gCofo *c) {
  if (c != NULL && c->numItens > 0) {
    for (int i = c->numItens - 1; i >= 0; i--) {
      c->item[i] = c->item[i - 1];
      c->numItens--;
    }
    return c->numItens;
  }

  return TRUE;
}

void *gcofQuery(gCofo *c, void *key, int (*cmp)(void *, void *)) {
  if (c != NULL && c->numItens > 0) {
    for (int i = 0; i < c->numItens; i++) {
      if (cmp(c->item[i], key)) {
        return c->item[i];
      }
    }
  }

  return NULL;
}

void *gcofRemove(gCofo *c, void *key, int (*cmp)(void *, void *)) {
  int i = 0, j;
  if (c != NULL && c->numItens > 0) {
    int stats = cmp(c->item[i], key);

    while (i < c->numItens && stats != TRUE) {
      i++;
      stats = cmp(c->item[i], key);
    }

    if (stats == TRUE) {
      void *data = c->item[i];

      for (j = i; j < c->numItens; j++) {
        c->item[j] = c->item[j + 1];
      }
      c->numItens--;
      return data;
    }
  }

  return NULL;
}

void *gcofGetFirst(gCofo *c) {
  if (c != NULL && c->numItens > 0) {
    c->cur = 0;

    return c->item[c->cur];
  }

  return NULL;
}

void *gcofGetNext(gCofo *c) {
  if (c != NULL && c->numItens > 0) {
    if (c->cur < c->numItens - 1) {
      c->cur++;

      return c->item[c->cur];
    }
  }

  return NULL;
}
