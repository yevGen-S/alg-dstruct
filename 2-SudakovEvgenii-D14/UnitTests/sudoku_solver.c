#include <stdio.h>
#include <string.h>
#include "sudoku_solver.h"
#include <windows.h>
#include <stdlib.h>
#pragma warning (disable: 4996)


int n;
int NUMBERS;
int ROWS;
int COLOUMNS;
int BLOCKS;


#define INIT_TIMER \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER start,end; \
    double result; \
    QueryPerformanceFrequency(&frequency);

#define TIMER_START QueryPerformanceCounter(&start);

#define TIMER_STOP \
    QueryPerformanceCounter(&end); \
    result =(float)(end.QuadPart-start.QuadPart)/frequency.QuadPart; \

#define BLOCK_NUM(row,coloumn) ((row / n) * n + (coloumn / n))


int checkBoard(int** board) {
	for (int i = 0; i < NUMBERS; i++) {
		for (int j = 0;  j < NUMBERS; j++) {
			if (board[i][j] > NUMBERS) {
				return 0;
			}
		}
	}
	return 1;
}


int findSolve(SudokuMeta* sudoku, int row, int coloumn) {
	if (row == ROWS - 1 && coloumn == COLOUMNS)
		return 1;

	if (coloumn == COLOUMNS) {
		coloumn = 0;
		row++;
	}

	if (sudoku->board[row][coloumn] == 0) {
		for (int val = 0; val < NUMBERS; val++) {
			if (sudoku->in_row_check[val][row] == 0 &&
				sudoku->in_coloumn_check[val][coloumn] == 0 &&
				sudoku->in_block_check[val][BLOCK_NUM(row, coloumn)] == 0) {
				sudoku->in_row_check[val][row] = 1;
				sudoku->in_coloumn_check[val][coloumn] = 1;
				sudoku->in_block_check[val][BLOCK_NUM(row, coloumn)] = 1;
				
				if (findSolve(sudoku, row, coloumn + 1) == 1) {
					sudoku->board[row][coloumn] = val + 1;
					return 1;
				}

				sudoku->in_row_check[val][row] = 0;
				sudoku->in_coloumn_check[val][coloumn] = 0;
				sudoku->in_block_check[val][BLOCK_NUM(row, coloumn)] = 0;
			}
		}
		return 0;
	}
	

	return findSolve(sudoku, row, coloumn + 1);
}



void solveSudoku(int** init_board, FILE* file) {
	SudokuMeta sudoku;
	sudoku.board = init_board;


	sudoku.in_block_check = (int**)malloc(sizeof(int*) * NUMBERS);
	sudoku.in_coloumn_check = (int**)malloc(sizeof(int*) * NUMBERS);
	sudoku.in_row_check = (int**)malloc(sizeof(int*) * NUMBERS);

	for (int i = 0; i < NUMBERS; i++) {
		sudoku.in_row_check[i] = (int*)malloc(sizeof(int) * NUMBERS);
		sudoku.in_coloumn_check[i] = (int*)malloc(sizeof(int) * NUMBERS);
		sudoku.in_block_check[i] = (int*)malloc(sizeof(int) * NUMBERS);
		memset(sudoku.in_row_check[i], 0, sizeof(int) * ROWS);
		memset(sudoku.in_coloumn_check[i], 0, sizeof(int) * COLOUMNS);
		memset(sudoku.in_block_check[i], 0, sizeof(int) * BLOCKS);

	}


	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLOUMNS; j++) {
			int val = init_board[i][j];
			if (val != 0) {
				sudoku.in_row_check[val - 1][i] = 1;
				sudoku.in_coloumn_check[val - 1][j] = 1;
				sudoku.in_block_check[val - 1][BLOCK_NUM(i, j)] = 1;
			}
		}
	}

	if (!findSolve(&sudoku, 0, 0)) {
		fprintf(stderr, "%s", "Error of sudoku start board, no solution");
		fprintf(file, "%i", 0);
	}
}


int** createBoardForSudoku(FILE * file) {
	int** board;

	fscanf(file, "%d", &n);
	if (n < 2) {
		fprintf(stderr, "%s", " Input please bigger dimension for board");
		exit(ERROR_SMALL_BOARD);
	}

	NUMBERS = ROWS = COLOUMNS = BLOCKS = n * n;

	board = (int**)malloc(sizeof(int*) * NUMBERS);
	for (int i = 0; i < NUMBERS; i++) {
		board[i] = (int*)malloc(sizeof(int) * NUMBERS);
	}

	for (int row = 0; row < NUMBERS; row++) {
		board[row] = (int*)malloc(sizeof(int) * NUMBERS );
		for (int coloumn = 0; coloumn < NUMBERS; coloumn++){
			fscanf(file, "%d", &board[row][coloumn]);
			if (board[row][coloumn] > NUMBERS) {
				fprintf(stderr, "%s", "Error of sudoku start board, no solution");
				exit(ERROR_BOARD);
			}
		}
	}
	
	fclose(file);
	return board;
}

void output(FILE* file, int** board) {
	
	fprintf(file, "%d\n", n);
	for (int row = 0; row < n * n; row++) {
		for (int coloumn = 0; coloumn < n * n; coloumn++) {
			fprintf(file, "%d ", board[row][coloumn]);
		}
		fprintf(file,"\n");
		free(board[row]);
	}
	fclose(file);
}



int main() {
	FILE* file_input = fopen("input.txt", "r");
	FILE* file_output = fopen("output.txt", "w");
	if (file_input == NULL || file_output == NULL) {
		fprintf(stderr, "%s", "Error of opening file");
		exit(ERROR_OPENNING_FILE);
	}

	INIT_TIMER
		TIMER_START
			int** board = createBoardForSudoku(file_input);
			solveSudoku(board, file_output);
			output(file_output, board);
		TIMER_STOP
	printf("Execution time: %lf", result);
	return 0;
}
