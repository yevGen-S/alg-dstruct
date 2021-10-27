#include "memallocator.h"
#include <stdio.h>
#include <inttypes.h>

#define TRUE 1
#define FALSE !TRUE
#define BLOCK_DATA(block) (void*)((byte*)block + sizeof(Descriptor))
#define BLOCK_HEADER(ptr) (Descriptor*)((byte*)ptr - sizeof(Descriptor))

typedef uint8_t byte;

typedef struct descriptor{
    struct descriptor* next;
    struct descriptor* prev;
    uint32_t blockSize;
    byte isUsed;
}Descriptor;

static Descriptor* firstHeader = NULL;
static uint32_t initSize;
static uint8_t flag = 1;


uint32_t memGetFullsize(){
    Descriptor * head = firstHeader;
    uint32_t currentSize = 0;
    while (head != NULL){
        currentSize += head->blockSize + sizeof(Descriptor);
        head = head->next;
    }
    return currentSize;
}


int memgetminimumsize(){
    return sizeof(Descriptor);
}


int memgetblocksize(){
    return sizeof(Descriptor);
}

Descriptor * getNewBlockPos(Descriptor* block, uint32_t size){
    return (Descriptor *)((byte*)block + sizeof(Descriptor) + sizeof(byte) * size);
}



byte mergeCheck(Descriptor* left, Descriptor* right){
    if (left == NULL || right == NULL){
        return FALSE;
    }
    uint32_t size;
    if(left->blockSize == 0 ){
        size = 1;
    }

    else {
        size = left->blockSize;
    }

    if(left->blockSize > 0){
        if((byte*)left+ sizeof(Descriptor)+sizeof(byte)*size == (byte*)right){
            return TRUE;
        }
    }

    return FALSE;
}

void memBlockCreate(Descriptor * block, uint32_t size){
    if (block->blockSize <= size)
        return;

    if(block->blockSize - size < sizeof(Descriptor)){
        return;
    }
    Descriptor* newBlock = getNewBlockPos(block,size);
    newBlock->next = block->next;
    newBlock->isUsed = FALSE;
    newBlock->prev = block;
    newBlock->blockSize = block->blockSize - size - sizeof(Descriptor);

    if (block->next != NULL)
        block->next->prev = newBlock;

    block->next = newBlock;
    block->blockSize = size;

}

int8_t memBlockMerge(Descriptor * left, Descriptor * right){
    if (left == NULL || right == NULL)
        return FALSE;

    if (!left->isUsed && !right->isUsed)
        if (mergeCheck(left, right)){
            if (right->next != NULL)
                right->next->prev = left;
            left->next = right->next;
            left->blockSize += right->blockSize + sizeof(Descriptor);

            return TRUE;
        }
    return FALSE;

}


int meminit(void* pMemory, int size){

    if(pMemory == NULL){
        fprintf(stderr,"%s","Empty pointer");
        return 0;
    }
    if(firstHeader != NULL){
        fprintf(stderr,"%s","Memory is inited");
        return 0;
    }
    if(size <= sizeof(Descriptor)){
        fprintf(stderr,"%s","Too little to init memory allocator");
        return 0;
    }
    firstHeader = (Descriptor *)pMemory;
    firstHeader->blockSize = size - sizeof(Descriptor);
    firstHeader->next= NULL;
    firstHeader->prev = NULL;
    firstHeader->isUsed = FALSE;

    initSize = size;
    return 1;
}

void memdone(){
    uint32_t fullSize = memGetFullsize();
    if (fullSize != initSize)
        fprintf(stderr, "Memory leak: init size = %i, current size = %i", initSize, fullSize);
    firstHeader = NULL;
}

Descriptor* getLastBlock(){
    Descriptor* finder = firstHeader;
    while(finder-> next !=NULL){
        finder = finder->next;
    }
    return finder;
}


void* memalloc(int size){
    if (flag){
        flag = !flag;
        Descriptor * fromFirstCursor = firstHeader;
        while (fromFirstCursor != NULL){
            if (!fromFirstCursor->isUsed && fromFirstCursor->blockSize >= size){
                memBlockCreate(fromFirstCursor, size);
                fromFirstCursor->isUsed = TRUE;
                return BLOCK_DATA(fromFirstCursor);
            }
            fromFirstCursor = fromFirstCursor->next;
        }
    }
    else{
        flag = !flag;
        Descriptor * fromLastCursor = getLastBlock();

        while (fromLastCursor != NULL){
            if (!fromLastCursor->isUsed && fromLastCursor->blockSize >= size){
                memBlockCreate(fromLastCursor, size);
                fromLastCursor->isUsed = TRUE;
                return BLOCK_DATA(fromLastCursor);
            }
            fromLastCursor = fromLastCursor->prev;
        }
    }
    fprintf(stderr, "No available memory for %d bytes!\n", size);
    return NULL;
}

void memfree(void* p){
    if (p == NULL)
        return;

    Descriptor * freeBlock = BLOCK_HEADER(p);

    freeBlock->isUsed = FALSE;

    if (freeBlock->prev != NULL)
        if (memBlockMerge(freeBlock->prev, freeBlock))
            freeBlock = freeBlock->prev;

    if (freeBlock->next != NULL)
        memBlockMerge(freeBlock, freeBlock->next);
}


