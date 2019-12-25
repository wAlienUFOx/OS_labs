#include <stdlib.h>
#include <stdio.h>
#include "str_deque.h"

extern str_deque* create();
extern void push_back(str_deque* deque, char* str);
extern void pop_back(str_deque* deque);
extern void push_front(str_deque* deque, char* str);
extern void pop_front(str_deque* deque);
extern void print(str_deque* deque);
extern void destroy(str_deque* deque);

int main(){
    str_deque* deque = create();
    pop_back(deque);
    print(deque);
    push_back(deque, "строка 1");
    print(deque);
    push_back(deque, "строка 2");
    push_front(deque, "строка 3");
    print(deque);
    pop_front(deque);
    pop_back(deque);
    print(deque);
    pop_back(deque);
    print(deque);
    destroy(deque);
    return 0;
}