#include "pch.h"

extern "C" {
#include "stack_on_arr.h"
#include "stack_on_list.h"
}

list_t* test_stack = CreateStack();

TEST(testStackOnList, handleCreateStackOnListFun) {	
	list_t* stack = CreateStack();
    EXPECT_TRUE(stack != NULL);
	EXPECT_TRUE(stack->head->next == NULL);
	EXPECT_TRUE(stack->length == 0);
	EXPECT_TRUE(stack->top == stack->head);
}

TEST(testStackOnList, handlePushInStackOnListFun) {
	Push(test_stack, 1);
	EXPECT_TRUE(test_stack->top->data == 1);
	EXPECT_TRUE(test_stack->head->next->data == 1);
	EXPECT_TRUE(test_stack->length == 1);
	Push(test_stack, 2);
	EXPECT_TRUE(test_stack->top->data == 2);
	EXPECT_TRUE(test_stack->head->next->next->data == 2);
	EXPECT_TRUE(test_stack->length == 2);
	Push(test_stack, 3);
	EXPECT_TRUE(test_stack->top->data == 3);
	EXPECT_TRUE(test_stack->head->next->next->next->data == 3);
	EXPECT_TRUE(test_stack->length == 3);
	Push(test_stack, 4);
	EXPECT_TRUE(test_stack->top->data == 4);
	EXPECT_TRUE(test_stack->length == 4);
}


TEST(testStackOnList, handlePopFromStackOnListFun) {
	Pop(test_stack);
	EXPECT_TRUE(test_stack->top->data == 3);
	EXPECT_TRUE(test_stack->length == 3);
}

TEST(testStackOnList, handleWatchTopElementInStackOnListFun) {
	EXPECT_EQ(Top(test_stack), test_stack->top->data);
}

TEST(testStackOnList, handleDeleteStackOnListFun) {
	EXPECT_EQ(DeleteStack(test_stack), 0);
}

TEST(testStackOnArr, handlePushInStackOnArrFun) {
	stack_on_arr_t stack_arr;
	stack_arr.length = 0;
	PushSA(&stack_arr, 1);
	EXPECT_TRUE(stack_arr.arr[stack_arr.length - 1] == 1);
	EXPECT_TRUE(stack_arr.length == 1);
	PushSA(&stack_arr, 2);
	EXPECT_TRUE(stack_arr.arr[stack_arr.length - 1] == 2);
	EXPECT_TRUE(stack_arr.length == 2);
	PushSA(&stack_arr, 3);
	EXPECT_TRUE(stack_arr.arr[stack_arr.length - 1] == 3);
	EXPECT_TRUE(stack_arr.length == 3);
}

TEST(testStackOnArr, handlePopFromStackOnArrFun) {
	stack_on_arr_t stack_arr2;
	stack_arr2.length = 0;
	PushSA(&stack_arr2, 1);
	PushSA(&stack_arr2, 2);
	PopSA(&stack_arr2);
	EXPECT_TRUE(stack_arr2.arr[0] == 1);
}

TEST(testStackOnArr, handleTopFromStackOnArrFun) {
	stack_on_arr_t stack_arr3;
	stack_arr3.length = 3;
	stack_arr3.arr[0] = 1;
	stack_arr3.arr[1] = 2;
	stack_arr3.arr[2] = 3;
	EXPECT_EQ(TopSA(&stack_arr3), 3);
}

