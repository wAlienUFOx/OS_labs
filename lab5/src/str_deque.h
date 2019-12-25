#ifndef STR_DEQUE_H
#define STR_DEQUE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node{
    struct node* next;
    struct node* prev;
    char* data;
} node;

typedef struct str_deque {
  node* Head;
  node* Tail;
  size_t size;
} str_deque;

#endif
