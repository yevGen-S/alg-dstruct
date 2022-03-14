#ifndef INC_2_SUDAKOVEVGENII_J11_CRC32_H
#define INC_2_SUDAKOVEVGENII_J11_CRC32_H
#include <inttypes.h> // uint32_t, uint8_t
#include<stdio.h>


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
#endif //INC_2_SUDAKOVEVGENII_J11_CRC32_H
