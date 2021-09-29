#pragma once



typedef struct node_t { // Node in list 
	struct node_t* next;
	int data;
}node_t;

typedef struct list_t {	// linked list
	node_t* head;
	node_t* top;
	unsigned int length;
}list_t;

list_t* CreateStack();				// function that create stack
int DeleteStack(list_t* stack);		// function that delete stack
void Push(list_t* stack, int data);	// function that add node to the end of the stack
void Pop(list_t* stack);			// function that delete node in the end of the stack
int Top(list_t* stack);				// function that show last node of the stack
