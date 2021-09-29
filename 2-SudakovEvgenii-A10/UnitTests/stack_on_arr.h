#pragma once
#define MAX_SIZE 50
#define data_t int

typedef struct stack_on_arr_t {
	data_t arr[MAX_SIZE];
	unsigned int length;
}stack_on_arr_t;

//SOA -- Stack on Array
void PushSA(stack_on_arr_t* stack, data_t data);
void PopSA(stack_on_arr_t* stack);
data_t TopSA(stack_on_arr_t* stack);

