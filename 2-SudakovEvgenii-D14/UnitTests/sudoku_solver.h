#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

typedef enum __error_t {
	ERROR_OPENNING_FILE,
	ERROR_BOARD,
	ERROR_SMALL_BOARD
}ERROR_T;

typedef struct SudokuMeta {
	int** in_row_check;
	int** in_coloumn_check;
	int** in_block_check;
	int** board;
} SudokuMeta;


int findSolve(SudokuMeta* sudoku, int row, int coloumn);
int checkBoard(int** board);
void solveSudoku(int** init_board, FILE* file);
int** createBoardForSudoku(FILE* file);
void output(FILE* file, int** board);

#endif // SUDOKU_SOLVE_H_INCLUDED
