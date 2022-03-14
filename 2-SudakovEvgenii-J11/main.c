#include <stdio.h>
#include "src/crc32.h"
#include <string.h>

int main(void) {
    char command;
    hashMap *map = NULL;
    map = mapInit(map);
    char value[100] = {'\0'};
    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q')
            getchar();
            gets(value);
        switch (command) {
            case 'a':
                mapAddItem(map, value);
                break;
            case 'r':
                mapRemoveItem(map, value);
                break;
            case 'f':
                if (mapSearch(map, value)) {
                    puts("yes");
                } else {
                    puts("no");
                }
                break;
            case 'p':
                mapPrint(map);
                putchar('\n');
                break;
            case 'q':
                mapDestroy(map);
                return 0;
        }
    }

}




