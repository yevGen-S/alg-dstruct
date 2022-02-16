#include <stdio.h>
#include <stdlib.h>
#include "src/aatree.h"
#include "src/binarytree.h"
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

#define MAX_NUMBER_OF_VALUES 1000

int main(void) {
//    char command;
//    int key;
//    int y = 1;
//    AATree *t = NULL;
//
//    AATreeInit();
//    printf("press a to add node\npress r to remove node\n"
//           "press f to find node\npress p to print tree\npress q to quit and delete tree\n");
//    while (scanf("%c", &command) >= 1) {
//        if (command != 'p' && command != 'q')
//            scanf("%i", &key);
//        switch (command) {
//            case 'a':
//                t = AATreeInsertNode(key, t);
//                break;
//            case 'r':
//                t = AATreeDeleteNode(key, t);
//                break;
//            case 'f':
//                if (AATreeSearch(t, key))
//                    puts("yes");
//                else
//                    puts("no");
//                break;
//            case 'p':
//                AATreePrint2(t);
//                putchar('\n');
//                break;
//            case 'q':
//                AATreeDestroy(t);
//                return 0;
//        }
//    }
    binaryTree *binary = NULL;
    AATree *aatree = NULL;
    AATreeInit();

    srand(time(NULL));
    FILE *file = fopen("compare.csv", "w");
    double res_binary;
    INIT_TIMER
    fprintf(file, "%s", "insert binary;insert aatree\n");
    if (file) {
        for (int i = 0; i < MAX_NUMBER_OF_VALUES; i++) {
            TIMER_START
            binary = BinaryTreeInsertNode(rand() % 1000 + 1, binary);
            TIMER_STOP
            res_binary = result;

            TIMER_START
            aatree = AATreeInsertNode(rand() % 1000 + 1, aatree);
            TIMER_STOP
            fprintf(file, "%.15f;%.15f\n", res_binary, result);
        }
        fprintf(file, "%s", "delete from binary; delete from aatree\n");
        for (int i = 0; i < MAX_NUMBER_OF_VALUES; i++) {
            TIMER_START
            binary = BinaryTreeDeleteNode(rand() % 1000 + 1, binary);
            TIMER_STOP
            res_binary = result;

            TIMER_START
            aatree = AATreeDeleteNode(rand() % 1000 + 1, aatree);
            TIMER_STOP
            fprintf(file, "%.15f;.15%f\n", res_binary, result);
        }
    }
    fclose(file);
    return 0;
}