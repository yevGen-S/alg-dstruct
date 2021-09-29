#include <stdio.h>
#include <stdlib.h>
#include "stack_on_list.h"

list_t* CreateStack() {
	list_t* stack = (list_t*)malloc(sizeof(list_t));
	node_t* head_node = (node_t*)malloc(sizeof(node_t));

	if (stack == NULL || head_node == NULL) {
		fprintf(stderr, "%s", "ERROR_MEMORY_ALLOC");
		exit(1);
	}

	stack->length = 0;
	stack->head = head_node;
	stack->top = head_node;
	head_node->next = NULL;
	return stack;
}

void DeleteStack(list_t* stack) {
	node_t* delete_node = stack->head;

	while (stack->head != NULL) {
		delete_node = stack->head;
		stack->head = stack->head->next;
		free(delete_node);
	}
}

void Push(list_t* stack, int node_data) {
	node_t* new_node = (node_t*)malloc(sizeof(node_t));

	if (new_node == NULL) {
		fprintf(stderr, "%s", "ERROR_MEMORY_ALLOC");
		exit(1);
	}

	new_node->data = node_data;
	stack->top->next = new_node;
	stack->top = stack->top->next;
	stack->top->next = NULL;
	stack->length += 1;
}

void Pop(list_t* stack) {
	if (stack->length < 1) {
		return;
	}

	node_t* node = stack->head;

	while (node->next != stack->top) {
		node = node->next;
	}
	
	node->next = stack->top->next;
	stack->top = node;
	stack->length -= 1;
	free(node->next);
}

int Top(list_t* stack) {
	if (stack == NULL) {
		fprintf(stderr, "%s", "STACK_DELETED");
		exit(1);
	}
	if (stack->length == 0) {
		fprintf(stderr, "%s", "EMPTY_STACK");
		exit(1);
	}
	return stack->top->data;
}

void PrintStack(list_t* stack) {
	if (stack == NULL) {
		return;
	}
	node_t* tmp_node = stack->head->next;
	while (tmp_node != NULL) {
		printf("%d ", tmp_node->data);
		tmp_node = tmp_node->next;
	}
	putchar('\n');
}
