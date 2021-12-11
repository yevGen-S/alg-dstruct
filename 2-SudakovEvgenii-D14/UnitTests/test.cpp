#include <gtest/gtest.h>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include "sudoku_solver.h"
}

#define SOLUTION_LEN 1000



TEST(SudokuHandleTest, check_sudoku_solved_4x4) {
	int** board;
	FILE* inputF = fopen("input.txt", "w");
	FILE* outputF = fopen("output.txt", "w");

	fprintf(inputF, "2\n"\
		"0 2 3 4\n"\
		"3 0 2 1\n"\
		"2 1 0 3\n"\
		"4 3 1 0\n"\
	);

	inputF = freopen("input.txt", "r", inputF);

	board = createBoardForSudoku(inputF);
	solveSudoku(board, outputF);
	output(outputF, board);

	char solution[SOLUTION_LEN] = { 0 };
	outputF = fopen("output.txt", "r");
	while (fgets(solution + strlen(solution), SOLUTION_LEN, outputF) != NULL);


	EXPECT_TRUE(strcmp(solution + 2, \
		"1 2 3 4 \n"		\
		"3 4 2 1 \n"		\
		"2 1 4 3 \n"		\
		"4 3 1 2 \n") == 0);
}

TEST(SudokuHandleTest, check_sudoku_is_filled) {
	int** board;
	FILE* inputF = fopen("input.txt", "w");
	FILE* outputF = fopen("output.txt", "w");

	fprintf(inputF, "2\n"\
		"1 2 3 4\n"\
		"3 4 2 1\n"\
		"2 1 4 3\n"\
		"4 3 1 2\n"\
	);

	inputF = freopen("input.txt", "r", inputF);

	board = createBoardForSudoku(inputF);
	solveSudoku(board, outputF);
	output(outputF, board);

	char solution[SOLUTION_LEN] = { 0 };
	outputF = fopen("output.txt", "r");
	while (fgets(solution + strlen(solution), SOLUTION_LEN, outputF) != NULL);


	EXPECT_TRUE(strcmp(solution + 2, \
		"1 2 3 4 \n"		\
		"3 4 2 1 \n"		\
		"2 1 4 3 \n"		\
		"4 3 1 2 \n") == 0);
}

TEST(SudokuHandleTest, check_sudoku_solved_9x9) {
	int** board;
	FILE* inputF = fopen("input.txt", "w");
	FILE* outputF = fopen("output.txt", "w");

	fprintf(inputF, "3\n"\
		"1 0 3 0 5 0 7 0 9\n" \
		"4 5 6 7 8 9 1 2 3\n" \
		"7 8 9 1 2 3 4 5 6\n" \
		"2 1 4 3 6 5 8 9 7\n" \
		"3 6 5 8 9 7 2 1 4\n" \
		"8 9 7 2 1 4 3 6 5\n" \
		"5 3 1 6 4 2 9 7 8\n" \
		"6 4 2 9 7 8 5 3 1\n" \
		"9 7 8 5 3 1 6 4 2" \
	);

	inputF = freopen("input.txt", "r", inputF);

	board = createBoardForSudoku(inputF);
	solveSudoku(board, outputF);
	output(outputF, board);

	char solution[SOLUTION_LEN] = { 0 };
	outputF = fopen("output.txt", "r");
	while (fgets(solution + strlen(solution), SOLUTION_LEN, outputF) != NULL);


	EXPECT_TRUE(strcmp(solution + 2, \
		"1 2 3 4 5 6 7 8 9 \n" \
		"4 5 6 7 8 9 1 2 3 \n" \
		"7 8 9 1 2 3 4 5 6 \n" \
		"2 1 4 3 6 5 8 9 7 \n" \
		"3 6 5 8 9 7 2 1 4 \n" \
		"8 9 7 2 1 4 3 6 5 \n" \
		"5 3 1 6 4 2 9 7 8 \n" \
		"6 4 2 9 7 8 5 3 1 \n" \
		"9 7 8 5 3 1 6 4 2 \n") == 0);
}

TEST(SudokuHandleTest, test_on_no_solution) {
	int** board;
	FILE* inputF = fopen("input.txt", "w");
	FILE* outputF = fopen("output.txt", "w");

	fprintf(inputF, "0\n"\
		"1 2 3 4\n"\
		"3 4 2 1\n"\
		"2 1 4 3\n"\
		"4 3 1 2\n"\
	);

	inputF = freopen("input.txt", "r", inputF);

	ASSERT_DEATH(board = createBoardForSudoku(inputF), "^ Input please bigger dimension for board$");
}

TEST(SudokuHandleTest, test_on_no_solution_2) {
	int** board;
	FILE* inputF = fopen("input.txt", "w");
	FILE* outputF = fopen("output.txt", "w");

	fprintf(inputF, "2\n"\
		"100 2 3 4\n"\
		"3 4 2 1\n"\
		"2 1 4 3\n"\
		"4 3 1 2\n"\
	);

	inputF = freopen("input.txt", "r", inputF);

	ASSERT_DEATH(board = createBoardForSudoku(inputF), "^Error of sudoku start board, no solution$");

}