//
// Created by dudar on 10/12/2019.
//

#ifndef SUDOKUX_LP1AED1_SUDOKUX_H
#define SUDOKUX_LP1AED1_SUDOKUX_H

#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSUDOKU 150
#define FILENAME "sudoku9x9_2.txt"
#define FILENAME_FACIL "sudoku9x9_facil.txt"
#define FILENAME_MEDIO "sudoku9x9_medio.txt"
#define FILENAME_DIFICIL "sudoku9x9_dificil.txt"
#define FILENAME_LARGE "sudoku16x16.txt"

#define SIZE 9
#define SUBMAT_SIZE sqrt(SIZE)

extern int UNSOLVED;

typedef struct Square{
    struct Square* N;
    struct Square* NE;
    struct Square* E;
    struct Square* SE;
    struct Square* S;
    struct Square* SO;
    struct Square* O;
    struct Square* NO;
    int number;

    /*  [0] [0] [0] [0] [0] [0] [0] [0] [0]     // quando a flag esta a 1 quer dizer que esse numero nao é possivel na celula, a 0 é possivel
        [9] [8] [7] [6] [5] [4] [3] [2] [1]   */
    int possible[9];
    int solvable;   //começa a 9 e quando só tem 1 possivel insere
    int box;
    int row;
    int column;
} SQUARE;

typedef struct Table{
    int line;
    SQUARE* psquare;
}TABLE;

typedef struct Sudoku{
    int nlines;
    int ncol;
    TABLE* ptable;
} SUDOKU;


void line_columns_from_txt(int *col, int* lin, char* filename);
char** read_file_to_pointer(int lin, int col, char* filename);
void create_array_tables(SUDOKU* ps, int lines, int cols);
void insert_cel_into_table(SUDOKU *ps, char** matrix);
void connect(SUDOKU* ps, SQUARE* cel_temp, SQUARE* cel_aux, int i, int j);

void print_sudoku(SUDOKU* s);


//BACKTRACKING
int solve_sudoku(SUDOKU* s);
int is_safe(int n, int r, int c, SUDOKU* s);
int number_unassigned(int *row, int *col, SUDOKU* s);


//SOLVE BY RULES
int checkPuzzle(SUDOKU* s);
int updateSudoku(SUDOKU* s, SQUARE* cel, int row, int col);
int solveSquare(SQUARE* cel);

int boxHiddenAloneNumber(SUDOKU* s);
int rowHiddenAloneNumber(SUDOKU* s);
int colHiddenAloneNumber(SUDOKU* s);
int boxAlonePairs(SUDOKU* s);
int checkRows(SUDOKU* s);
int checkColumns(SUDOKU* s);


//SAVE
void WritePuzzleInFileTXT(SUDOKU* s, char *filename);
void WritePuzzleInFileBIN(SUDOKU* s, char *filename);


//TEST
int main_fase2_menu();
int main_test_possibilities();
int main_test2();
int main_test2_backtracking();

void print_sudoku_possibilities(SUDOKU* s);
int calc_num_restantes(SUDOKU* s);

#endif //SUDOKUX_LP1AED1_SUDOKUX_H