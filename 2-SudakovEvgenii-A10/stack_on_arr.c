#include <stdio.h>
#include <stdlib.h>
#include "stack_on_arr.h"

void Push_SA(stack_on_arr_t* stack, data_t data) { 
	if (stack->length >= MAX_SIZE) {
		fprintf(stderr, "%s", "STACK_OVERFLOW");
		exit(-1);
	}
	stack->arr[stack->length] = data;
	stack->length++;
}

void Pop_SA(stack_on_arr_t* stack) {
	if (stack->length <= 0) {
		fprintf(stderr, "%s", "STACK_UNDERFLOW");
		exit(-2);
	}
	stack->length--;
}

data_t Top_SA(stack_on_arr_t* stack) {
	return (stack->length > 0) ? stack->arr[stack->length - 1] : fprintf(stderr,"%s","STACK_UNDERFLOW");
}

void PrintStack_SA(stack_on_arr_t* stack) {
	for (int i = 0; i < stack->length; i++) {
		printf("%d ", stack->arr[i]);
	}
	putchar('\n');
}
