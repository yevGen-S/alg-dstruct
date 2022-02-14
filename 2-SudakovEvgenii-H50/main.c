#include <stdio.h>
#include <stdlib.h>
#include "src/aatree.h"





int main(void) {
    char command;
    int key;
    int y = 1;
    AATree *t = NULL;
    AATreeInit();
    printf("press a to add node\npress r to remove node\n"
           "press f to find node\npress p to print tree\npress q to quit and delete tree\n");
    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q')
            scanf("%i", &key);
        switch (command) {
            case 'a':
                t = AATreeInsertNode(key, t);
                break;
            case 'r':
                t = AATreeDeleteNode(key, t);
                break;
            case 'f':
                if (AATreeSearch(t, key))
                    puts("yes");
                else
                    puts("no");
                break;
            case 'p':
                AATreePrint2(t);
                putchar('\n');
                break;
            case 'q':
                AATreeDestroy(t);
                return 0;
        }
    }

}
