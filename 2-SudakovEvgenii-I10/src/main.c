#include "2_3tree.h"
#include <stdio.h>
#include <stdlib.h>



int main(void) {
    char command;
    node *t = NULL;
    int y = 1;
    int key =0;
    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q')
            scanf("%i", &key);
        switch (command) {
            case 'a':
                t = insert_node(t, key);
                break;
            case 'r':
                t = remove_node(t, key);
                break;
            case 'f':
                if (search(t, key)) {
                    puts("yes");
                }
                else {
                    puts("no");
                }
                break;
            case 'p':
                print_tree(t);
                putchar('\n');
                break;
            case 'q':
                destroy_tree(t);
                return 0;
        }
    }



}