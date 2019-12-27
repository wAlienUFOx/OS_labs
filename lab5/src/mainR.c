#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "str_deque.h"

int main(){
    void *lib = dlopen("./str_deque.so", RTLD_LAZY);
    if (!lib) {
      printf("dlopen error\n");
        return -1;
    }

    str_deque*(*create)() = dlsym(lib, "create");
    _Bool(*empty)(str_deque* deque) = dlsym(lib, "empty");
    void(*push_back)(str_deque* deque, char* str) = dlsym(lib, "push_back");
    void(*pop_back)(str_deque* deque) = dlsym(lib, "pop_back");
    void(*push_front)(str_deque* deque, char* str) = dlsym(lib, "push_front");
    void(*pop_front)(str_deque* deque) = dlsym(lib, "pop_front");
    void(*print)(str_deque* deque) = dlsym(lib, "print");
    void(*destroy)(str_deque* deque) = dlsym(lib, "destroy");
    if(create == NULL || empty == NULL || push_back == NULL || pop_back == NULL ||
    push_front == NULL || pop_front == NULL || print == NULL || destroy == NULL){
        printf("dlsym error\n");
	return -1;
    }

    str_deque* deque = (create)();
    (*pop_back)(deque);
    (*print)(deque);
    (*push_back)(deque, "строка 1");
    (*print)(deque);
    (*push_back)(deque, "строка 2");
    (*push_front)(deque, "строка 3");
    (*print)(deque);
    (*pop_front)(deque);
    (*pop_back)(deque);
    (*print)(deque);
    (*pop_back)(deque);
    (*print)(deque);
    (*destroy)(deque);

    dlclose(lib);
    return 0;
}
