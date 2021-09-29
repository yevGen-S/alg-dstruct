#include "pch.h"

extern "C" {
#include "stack_on_arr.h"
#include "stack_on_list.h"
}

list_t* test_stack = CreateStack();

TEST(testStackOnList, handleCreateStackOnListFun) {	
	list_t* stack = CreateStack();
    EXPECT_TRUE(stack != NULL);
}

TEST(testStackOnList, handlePushInStackOnListFun) {
	Push(test_stack, 1);
	EXPECT_TRUE(test_stack->top->data == 1);
	Push(test_stack, 2);
}

TEST(testStackOnList, handlePopFromStackOnListFun) {
	Pop(test_stack);
	EXPECT_TRUE(test_stack->top->data == 1);
}

TEST(testStackOnList, handleWatchTopElementInStackOnListFun) {
	EXPECT_EQ(Top(test_stack), test_stack->top->data);
}

TEST(testStackOnList, handleDeleteStackOnListFun) {
	EXPECT_EQ(DeleteStack(test_stack), 0);
}

