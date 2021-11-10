#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bfs.h"
#include "windows.h"
#define NUMBER_OF_VERTICES 50000


#define INIT_TIMER \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER start,end; \
    double result; \
    QueryPerformanceFrequency(&frequency);

#define TIMER_START QueryPerformanceCounter(&start);

#define TIMER_STOP \
    QueryPerformanceCounter(&end); \
    result =(float)(end.QuadPart-start.QuadPart)/frequency.QuadPart; \


queue_t* CreateQueue(){
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if( queue == NULL ){
        fprintf( stderr, "%s", "Error of memory allocating");
        exit(ERROR_MEM_ALLOC);
    }
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}


void AddNodeToQueue(queue_t * queue, int number){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if( newNode == NULL){
        fprintf(stderr,"%s","Error of memory allocating");
        exit(ERROR_MEM_ALLOC);
    }

    if(queue->head == NULL){
        queue->head = newNode;
        queue->head->data = number;
        queue->head->next = NULL;
        queue->tail = queue->head;
    }
    else {
        queue->tail->next = newNode;
        newNode->next = NULL;
        newNode->data = number;
        queue->tail = newNode;
    }

}

void DeleteNodeFromQueue(queue_t* queue){
    if(queue == NULL){
        fprintf(stderr,"%s","Error empty pointer on queue");
        exit(EMPTY_PTR);
    }
    node_t* deleteNode = queue->head;
    queue->head = queue->head->next;
    free(deleteNode);
}

void DeleteQueue(queue_t* queue){
    if(queue == NULL || queue->head == NULL){
        fprintf(stderr,"%s","Error empty pointer on queue");
        exit(EMPTY_PTR);
    }

    node_t* deleteNode = queue->head;
    queue->head = queue->head->next;
    while(deleteNode->next != NULL){
        free(deleteNode);
        deleteNode = queue->head;
        queue->head = queue->head->next;

    }
}


graph_t* GetGraph(FILE* file){
    graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
    if(graph == NULL ){
        fprintf(stderr,"%s","Error of allocating memory");
        exit(ERROR_MEM_ALLOC);
    }
    graph->numberOfEdges =1;
    graph->data = (int*)malloc(2 * graph->numberOfEdges * sizeof(int) + 1);
    if(graph->data == NULL ) {
        fprintf(stderr, "%s", "Error of allocating memory");
        exit(ERROR_MEM_ALLOC);
    }


    int* checkR;
    int i = 0;
    fscanf(file,"%i",&graph->numberOfVertices);

    while(!feof(file)){
        fscanf(file, "%i %i\n", &graph->data[i], &graph->data[i + 1]);
        i += 2;
        graph->numberOfEdges++;
        checkR = (int *) realloc(graph->data, 2 * graph->numberOfEdges * sizeof(int) + 1);
        if (checkR != NULL)
            graph->data = checkR;


    }

    return graph;
}


int** CreateAdjencyMatrix(graph_t* graph){
    int** adjencyMatrix = (int**)malloc(graph->numberOfVertices* sizeof(int*));
    if( adjencyMatrix == NULL){
        fprintf(stderr,"%s","Error of allocting memory");
        exit(ERROR_MEM_ALLOC);
    }
    for(int i =0; i< graph->numberOfVertices; i++){
        adjencyMatrix[i] = (int*)calloc(graph->numberOfVertices, sizeof(int));
    }
    for(int i = 0; i < (graph->numberOfEdges-1)*2;i+=2){
        adjencyMatrix[graph->data[i]][graph->data[i+1]] = 1;
        adjencyMatrix[graph->data[i+1]][graph->data[i]] = 1;
    }
    return adjencyMatrix;
}



boolean IsQueueEmpty(queue_t* queue){
    if(queue==NULL || queue->head == NULL){
        return TRUE;
    }
    return FALSE;
}

void bfs(FILE* file){
    if(file == NULL){
        file = stdin;
    }

    queue_t* queue = CreateQueue();
    graph_t * graph = GetGraph(file);
    int** adjencyMatrix = CreateAdjencyMatrix(graph);
    AddNodeToQueue(queue,0);
    int* visitedNodes = (int*)calloc(graph->numberOfVertices,sizeof(int));
    if( visitedNodes == NULL){
        fprintf(stderr,"%s","Error of allocating memory");
        exit(ERROR_MEM_ALLOC);
    }

    node_t* cur = queue->head;
    while(!IsQueueEmpty(queue)) {
        for (int j = 0; j < graph->numberOfVertices; j++) {
            if (adjencyMatrix[cur->data][j] == 1) {
                if(visitedNodes[j] == 1){
                    continue;
                }
                AddNodeToQueue(queue, j);
                visitedNodes[j] = 1;
                visitedNodes[cur->data]=1;
            }
        }
        printf("%i ",cur->data);
        cur = cur->next;
        DeleteNodeFromQueue(queue);
    }
    free(visitedNodes);
}

void StressTest(FILE* file){
    srand(time(NULL));

    fprintf(file, "%d\n", NUMBER_OF_VERTICES + 2);
    fprintf(file, "0 1\n");

    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        fprintf(file, "%d %d\n", 1 + rand() % (NUMBER_OF_VERTICES/100),rand() % NUMBER_OF_VERTICES);

    }

    fprintf(file, "\n");

    fseek(file, SEEK_SET, 0);

    INIT_TIMER
    TIMER_START
    bfs(file);
    TIMER_STOP
    printf("\ntime = %lf",result);

    fclose(file);
}