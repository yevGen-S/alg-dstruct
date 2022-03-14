
#include <inttypes.h> // uint32_t, uint8_t
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAP_SIZE 512000
#define  True 1
#define False !(True)


typedef struct slots{
    char* value;
    struct slots* next;
}slots;


slots* slotSearch(slots* slot, char* string);
slots* slotRemove(slots* slot,char* string);
slots* slotAdd(slots* slot, char* string);
void slotPrint(slots* slot);
void slotDestroy(slots* slot);
int slotCounter(slots* slot);



typedef struct hashMapItem {
    char isFilled;
    slots* slot;
}hashMapItem;


typedef struct hashMap{
    hashMapItem* items;
    uint32_t size;
}hashMap;


hashMap *mapInit(hashMap* map);
void mapAddItem(hashMap* map, char* string);
void mapRemoveItem(hashMap* map, char* string);
char mapSearch(hashMap* map, char* string);
void mapDestroy(hashMap* map);
void mapPrint(hashMap* map);
char checkCollision(hashMap* map, char* string);

void createCRCTable(void);
unsigned int getCRC32(void *buffer, unsigned int bufferLen);


int bufflen(char* buffer);




unsigned int CRC32_Table[256];


hashMap *mapInit(hashMap* map){
    if(map == NULL){
        map = (hashMap*)malloc(sizeof(hashMap));
        if(map == NULL){
            return NULL;
        }
        map->size = MAP_SIZE;
        hashMapItem * tmpItems = (hashMapItem *)malloc(map->size * sizeof(hashMapItem) );
        if(tmpItems == NULL){
            return NULL;
        }
        map->items = tmpItems;
        for( int i = 0; i< map->size; i ++){
            map->items[i].isFilled = False;
            map->items[i].slot = NULL;
        }
        createCRCTable();
        return map;
    }
    return NULL;
}


int bufflen(char* buffer){
    int len = 0;
    if(buffer == NULL){
        return 0;
    }
    while(buffer[len]!='\0'){
        len++;
    }
    return len;
}


void mapAddItem(hashMap* map, char* string){
    if(map != NULL && map->items != NULL && string != NULL) {
        if (mapSearch(map,string)){
            return;
        }
        uint32_t hash = getCRC32(string, bufflen(string));
        uint32_t index = hash % MAP_SIZE;

        map->items[index].slot = slotAdd(map->items[index].slot, string);
        map->items[index].isFilled = True;
//        printf("\nindex=  %i:", index);
//        slotPrint(map->items[index].slot);
//        printf("\n");

    }
}

int slotCounter(slots* slot){
    int counter = 0;
    if(slot == NULL){
        return counter;
    }
    while( slot!= NULL){
        counter ++;
        slot= slot->next;
    }
    return counter;
}


void mapRemoveItem(hashMap* map, char* string){
    if(map != NULL && map->items != NULL && string != NULL) {
        if(!mapSearch(map,string)){
            return;
        }
        uint32_t hash = getCRC32(string, bufflen(string));
        uint32_t index = hash % MAP_SIZE;

        map->items[index].slot = slotRemove(map->items[index].slot, string);
        if(slotCounter(map->items[index].slot) == 0)
            map->items[index].isFilled = False;
//        printf("\nindex=  %i: ", index);
//        slotPrint(map->items[index].slot);
//        printf("\n");
    }
}

char checkCollision(hashMap* map, char* string){
    if(map != NULL && map->items!=NULL && string!=NULL){
        uint32_t hash = getCRC32(string, bufflen(string));
        uint32_t index = hash % MAP_SIZE;

        if(map->items[index].isFilled == False ){
            return False;
        }
        if(map->items[index].isFilled && strcmp(map->items[index].slot->value,string)!=0){
            return True;
        }
    }
    return False;
}




char mapSearch(hashMap* map, char* string){
    if(map != NULL && map->items!=NULL && string!=NULL){
        uint32_t hash = getCRC32(string, bufflen(string));
        uint32_t index = hash % MAP_SIZE;

        if(map->items[index].isFilled == False ){
            return False;
        }

        if (slotSearch(map->items[index].slot, string) != NULL) {
            return True;
        }

    }
    return False;
}


void mapDestroy(hashMap* map){
    if(map == NULL) {
        return;
    }
    else{
        for(int i = 0; i < map->size; i++){
            if(map->items[i].isFilled)
                slotDestroy(map->items[i].slot);
        }
        free(map->items);
    }
    free(map);
}

void mapPrint(hashMap* map){
    if( map != NULL){
        for(int i =0 ; i < map->size; i++){
            if(map->items[i].isFilled){
                slotPrint(map->items[i].slot);
            }
        }
    }
}

void createCRCTable(void){
    uint32_t crc32;
    unsigned int index = 0;
    unsigned int bit = 0;

    for(index = 0; index < 256; index++){
        crc32 = index;

        for(bit = 0; bit < 8; bit++){
            if(crc32 & 1){
                crc32 = (crc32 >> 1) ^ (0xEDB88320);
            }
            else{
                crc32 = crc32 >> 1;
            }

        }
        CRC32_Table[index] = crc32;
    }
}

unsigned int getCRC32(void *buffer, unsigned int bufferLen){
    uint32_t crc32Value = 0xffffffff;

    unsigned char *tmpBuffer =(unsigned char*) buffer;

    while(bufferLen--){
        crc32Value = CRC32_Table[(crc32Value ^ *tmpBuffer++) & 0xff] ^ (crc32Value >> 8);
    }

    return (crc32Value^0xffffffff);
}




slots* slotSearch(slots* slot, char* string){
    if (slot == NULL){
        return NULL;
    }
    while(slot != NULL){
        if(strcmp(slot->value, string ) == 0)
            return slot;
        slot = slot->next;
    }
    return NULL;
}



slots* slotAdd(slots* slot, char* string){
    if(slot == NULL){
        slots* newSlot = (slots*)malloc(sizeof(slots));
        if(newSlot!= NULL){
            slot = newSlot;
        }
        slot->value = (char*)malloc(sizeof(char)* bufflen(string));
        if(slot->value != NULL){
            strcpy(slot->value, string);
        }
        slot->next = NULL;
        return slot;
    }
    else{
        slots* tmp = slot;
        while(tmp->next!=NULL){
            tmp = tmp->next;
        }

        slots* newSlot = (slots*)malloc(sizeof(slots));
        newSlot->value = (char*)malloc(sizeof(char)* bufflen(string));
        if(newSlot != NULL && newSlot->value != NULL){
            tmp->next = newSlot;
            newSlot->next = NULL;
            strcpy(newSlot->value, string);

        }
        return slot;
    }
}


slots* slotRemove(slots* slot,char* string){
    if(slot== NULL){
        return NULL;
    }
    slots* removeSlot = slotSearch(slot, string);
    if(slot == removeSlot){
        slot = slot->next;
        free(removeSlot);
        return slot;
    }
    else{
        slots* tmp = slot;
        while(tmp->next != removeSlot){
            tmp = tmp->next;
        }
        tmp->next = removeSlot->next;
        free(removeSlot->value);
        free(removeSlot);
    }

    return slot;
}

void slotDestroy(slots* slot){
    slots* remove = slot;
    while(slot!= NULL){
        slot= remove->next;
        free(remove);
        remove = slot;
    }
}


void slotPrint(slots* slot){
    if(slot == NULL){
        return;
    }
    while(slot != NULL){
        printf("%s ",slot->value);
        slot= slot->next;
    }
}

int main(void) {
    char command;
    hashMap *map = NULL;
    map = mapInit(map);
    char value[100] = {'\0'};
    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q')
            getchar();
            fgets(value,sizeof(value),stdin);
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