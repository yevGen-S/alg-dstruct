#ifndef LABC_BFS_H
#define LABC_BFS_H

#endif //LABC_BFS_H

typedef enum ERRORS{
    EMPTY_PTR,
    ERROR_FILE_OPENING,
    ERROR_MEM_ALLOC,
}error_t;


typedef struct node{
    struct node* next;
    int data;
}node_t;

typedef struct Queue{
    node_t* head;
    node_t* tail;
}queue_t;

typedef struct graph{
    int* data;
    int numberOfEdges;
    int numberOfVertices;
}graph_t;

typedef char boolean;
#define TRUE 1
#define FALSE (!TRUE)


queue_t* CreateQueue();
void AddNodeToQueue(queue_t* queue,int number);
void DeleteNodeFromQueue(queue_t* queue);
void DeleteQueue(queue_t* queue);
graph_t* GetGraph(FILE* file);
int** CreateAdjencyMatrix(graph_t* graph);
boolean IsQueueEmpty(queue_t* queue);
void bfs(FILE* file);
void StressTest(FILE* file);