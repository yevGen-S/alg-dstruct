#include <stdio.h>
#include <stdlib.h>
#include "stack_on_arr.h"

typedef enum ERRORS{
	STACK_OVERFLOW,
	STACK_UNDERFLOW
}error_t;


void PushSA(stack_on_arr_t* stack, data_t data) { 
	if (stack->length >= MAX_SIZE) {
		fprintf(stderr, "%s", "STACK_OVERFLOW");
		exit(STACK_OVERFLOW);
	}
	stack->arr[stack->length] = data;
	stack->length++;
}

void PopSA(stack_on_arr_t* stack) {
	if (stack->length <= 0) {
		fprintf(stderr, "%s", "STACK_UNDERFLOW");
		exit(STACK_UNDERFLOW);
	}
	stack->length--;
}

data_t TopSA(stack_on_arr_t* stack) {
	return (stack->length > 0) ? stack->arr[stack->length - 1] : fprintf(stderr,"%s","STACK_UNDERFLOW");
}
