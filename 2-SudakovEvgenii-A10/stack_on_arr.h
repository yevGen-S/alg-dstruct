#pragma once
#define MAX_SIZE 50
#define data_t int

typedef struct stack_on_arr_t {
	data_t arr[MAX_SIZE];
	unsigned int length;
}stack_on_arr_t;

//SA -- Stack on Array
void Push_SA(stack_on_arr_t* stack, data_t data);
void Pop_SA(stack_on_arr_t* stack);
data_t Top_SA(stack_on_arr_t* stack);
void PrintStack_SA(stack_on_arr_t* stack);





