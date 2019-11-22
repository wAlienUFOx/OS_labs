#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX 4700

int THREAD_MAX;
int k;

struct Args {
    char **arr;
    int l;
    int r;
};
typedef struct Args Args;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void swap(char **o1, char **o2) {
    char *tmp = *o1;
    *o1 = *o2;
    *o2 = tmp;
}

int Partion(char **arr, int l, int r) {
    char *x = arr[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++) {
        if (strcmp(arr[j], x) <= 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[r]);

    return i + 1;
}

void *quick_sort(void *arg){
    Args args = *((Args *) arg);
    if(args.l < args.r){
        int q = Partion(args.arr, args.l, args.r);
        Args left;
        left.arr = args.arr;
        left.l = args.l;
        left.r = q - 1;
        Args right;
        right.arr = args.arr;
        right.l = q + 1;
        right.r = args.r;
        if(THREAD_MAX != 0){
            pthread_t left_thread;
            THREAD_MAX --;
	    k++;
            pthread_create(&left_thread, NULL, &quick_sort, &left);
            quick_sort(&right);
            pthread_join(left_thread, NULL);
        }
        else{
            quick_sort(&left);
            quick_sort(&right);
        }
    }
    return NULL;
}

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Error. Input number of threads.\n");
        return 0;
    }
    int s;
    int arg = atoi(argv[1]);
    k = 0;
    THREAD_MAX = min(max(arg, 1), MAX) - 1;

    printf("Input array size\n");
    scanf("%d", &s);
    char **arr = (char **) malloc(sizeof(char *) * s);
    for (int i = 0; i < s; i++) {
        arr[i] = (char *) malloc(sizeof(char) * 30);
        scanf("%s", arr[i]);
    }

    Args args;
    args.arr = arr;
    args.l = 0;
    args.r = s - 1;

    pthread_t first_thread;
    pthread_create(&first_thread, NULL, &quick_sort, &args);
    k++;
    pthread_join(first_thread, NULL);

    printf("\nResult:\n");
    for (int i = 0; i < s; i++)
        printf("%s\n", arr[i]);
    printf("Number of threads: %d\n", k);
    return 0;
}
