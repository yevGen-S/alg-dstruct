#define _CRT_SECURE_NO_WARNINGS
#include "memallocator.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define INIT_TIMER \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER start,end; \
    double result; \
    QueryPerformanceFrequency(&frequency);

#define TIMER_START QueryPerformanceCounter(&start);

#define TIMER_STOP \
    QueryPerformanceCounter(&end); \
    result =(float)(end.QuadPart-start.QuadPart)/frequency.QuadPart; \

#define MAX_ALLOC_SIZE 1000
#define MAX_ITER 1000

double mallocTestTime[MAX_ITER];
double memallocTestTime[MAX_ITER];

typedef enum errors {
    ERROR_OPENING_FILE,
    MEM_ALOC_ERROR,

}error_t;

double mallocTest(int size) {
    INIT_TIMER

    char* arr[MAX_ITER] = { NULL };
    int last_i = 0;
    TIMER_START
    for (int i = 0; i < MAX_ITER; i++) {
        arr[i] = malloc(rand() % MAX_ALLOC_SIZE);
        free(arr[i]);
    }
    TIMER_STOP

    return result;
}

double memallocTest(int size) {
    INIT_TIMER

    char* arr[MAX_ITER] = { NULL };
    int last_i = 0;
    TIMER_START
    for (int i = 0; i < MAX_ITER; i++) {
        arr[i] = memalloc(rand() % MAX_ALLOC_SIZE);
        memfree(arr[i]);
    }

    TIMER_STOP
    return result;
}

int main() {
    FILE* file = fopen("compare.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "%s", "Error of opening file!");
        exit(ERROR_OPENING_FILE);
    }
    void* pMemory = malloc(MAX_ITER * (MAX_ALLOC_SIZE + memgetblocksize()));
    if (pMemory == NULL) {
        fprintf(stderr, "%s", "Error of allocating memory");
        exit(MEM_ALOC_ERROR);
    }
    meminit(pMemory, MAX_ITER * (MAX_ALLOC_SIZE + memgetblocksize()));

    double column[2];
    fprintf(file, "iteration;malloc;memalloc\n");
    int k = 1;
    for (int i = 1; i < MAX_ALLOC_SIZE; i += 1) {
        column[0] = mallocTest(i);
        column[1] = memallocTest(i);
        fprintf(file, "%i;%lf;%lf\n",k, column[0], column[1]);
        k++;
    }
    fclose(file);
    return 0;
}