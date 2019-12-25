#include "str_deque.h"

str_deque* create(){
  str_deque* deque = (str_deque*)malloc(sizeof(str_deque));
  deque->Head = NULL;
  deque->Tail = NULL;
  deque->size = 0;
  return deque;
}

_Bool empty(str_deque* deque){
  if(deque->size == 0)
    return 1;
  else
    return 0;
}

void push_back(str_deque* deque, char* str){
  node* newnode = (node*)malloc(sizeof(node));
  newnode->next = NULL;
  newnode->data = str;
  if(empty(deque)){
    deque->Head = newnode;
    deque->Tail = newnode;
    newnode->prev = NULL;
    deque->size++;
    return;
  }
  deque->Tail->next = newnode;
  newnode->prev = deque->Tail;
  deque->Tail = newnode;
  deque->size++;
}

void pop_back(str_deque* deque){
  if (empty(deque)){
    printf("Error. Deque is empty.\n");
    return;
  }
  if(deque->size == 1){
    free(deque->Tail);
    deque->Head = NULL;
    deque->Tail = NULL;
    deque->size --;
    return;
  }
  node* tmp;
  tmp = deque->Tail->prev;
  deque->Tail = tmp;
  free(tmp->next);
  tmp->next = NULL;
  deque->size--;
}

void push_front(str_deque* deque, char* str){
  node* newnode = (node*)malloc(sizeof(node));
  newnode->prev = NULL;
  newnode->data = str;
  if(empty(deque)){
    deque->Head = newnode;
    deque->Tail = newnode;
    newnode->next = NULL;
    deque->size++;
    return;
  }
  deque->Head->prev = newnode;
  newnode->next = deque->Head;
  deque->Head = newnode;
  deque->size++;
}

void pop_front(str_deque* deque){
  if (empty(deque)){
    printf("Error. Deque is empty.\n");
    return;
  }
  if(deque->size == 1) {
    free(deque->Tail);
    deque->Head = NULL;
    deque->Tail = NULL;
    deque->size--;
    return;
  }
  node* tmp;
  tmp = deque->Head->next;
  deque->Head = tmp;
  free(tmp->prev);
  tmp->prev = NULL;
  deque->size--;
}

void print_node(node* node){
    printf("%s\n", node->data);
    if(node->next == NULL){
        return;
    }
    print_node(node->next);
}


void print(str_deque* deque){
  if (empty(deque)){
    printf("Error. Deque is empty.\n");
    return;
  }
  printf("----------\n");
  print_node(deque->Head);
  printf("++++++++++\n");
}

void destroy(str_deque* deque) {
  while(!empty(deque)){
    pop_back(deque);
  }
  free(deque);
  deque = NULL;
}