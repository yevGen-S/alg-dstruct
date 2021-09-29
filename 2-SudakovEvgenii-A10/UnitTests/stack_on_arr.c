#include <stdio.h>
#include <stdlib.h>
#include "stack_on_arr.h"

//void CreateStackSA(size_t n) {
//	stack_on_arr_t* stack;
//	stack->arr = (data_t*)malloc(sizeof(data_t) * n);
//	if (stack->arr == NULL) {
//		fprintf(stderr, "%s", "ERROR_MEMORY_ALOC");
//		exit(-1);
//	}
//}

void PushSA(stack_on_arr_t* stack, data_t data) { 
	if (stack->length >= MAX_SIZE) {
		fprintf(stderr, "%s", "STACK_OVERFLOW");
		exit(-1);
	}
	stack->arr[stack->length] = data;
	stack->length++;
}

void PopSA(stack_on_arr_t* stack) {
	if (stack->length <= 0) {
		fprintf(stderr, "%s", "STACK_UNDERFLOW");
		exit(-2);
	}
	stack->length--;
}

data_t TopSA(stack_on_arr_t* stack) {
	return (stack->length > 0) ? stack->arr[stack->length - 1] : fprintf(stderr,"%s","STACK_UNDERFLOW");
}
