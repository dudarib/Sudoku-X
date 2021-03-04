//
// Created by dudar on 04/12/2019.
//

#include "sudokuX.h"

int main_fase2_menu(){
    int choice, choice2;
    int col=0;
    int lin=0;
    int progress;
    int num_restantes;

    char filename[100];
    int k=0, b=0;

    do
    {
        printf("###################  SUDOKU X  ###################\n\n");
        printf("Escolha um nivel de dificuldade para o Sudoku:\n");
        printf("1. FACIL\n");
        printf("2. MEDIO\n");
        printf("3. DIFICIL\n");

        printf("\n0. SAIR\n");
        scanf("%d",&choice);


        switch(choice)
        {
            case 1: {
                SUDOKU sudoku={0, 0, NULL};
                col=0;
                lin=0;

                line_columns_from_txt(&col, &lin, FILENAME_FACIL);
                char** matriz_sudoku=read_file_to_pointer(lin, col, FILENAME_FACIL);
                create_array_tables(&sudoku, lin, col);
                insert_cel_into_table(&sudoku, matriz_sudoku);

                num_restantes = 81 - calc_num_restantes(&sudoku);

                print_sudoku(&sudoku);

                printf("\n");

                do
                {
                    printf("Escolha uma das opcoes:\n");
                    printf("1. ->Resolver Sudoku pelas Regras\n");
                    printf("2. ->Resolver Sudoku por BackTracking\n");
                    printf("3. ->Guardar Sudoku como Ficheiro de texto\n");
                    printf("4. ->Guardar Sudoku como Ficheiro Binario\n");
                    printf("\n0. Voltar para o Menu anterior\n");
                    scanf("%d",&choice2);

                    switch(choice2)
                    {
                        case 1: {
                            ///RULES
                            printf("\n");
                            print_sudoku(&sudoku);
                            printf("\n");

                            while (num_restantes > 0) {
                                progress = checkPuzzle(&sudoku);
                                num_restantes--;
                                //printf("faltam %d numeros\n", num_restantes);
                                if (progress == 0) {
                                    //printf("Escolha a opcao 2. para resolver por BackTracking\n");
                                    break;
                                }
                            }
                            print_sudoku(&sudoku);
                            break;
                        }
                        case 2: {
                            ///backtracking

                            printf("\n");
                            print_sudoku(&sudoku);
                            printf("\n");

                            solve_sudoku(&sudoku);
                            print_sudoku(&sudoku);
                            break;
                        }
                        case 3: {
                            sprintf(filename, "Sudoku_TXT-%02d.txt", k);
                            k++;
                            WritePuzzleInFileTXT(&sudoku, filename);
                            break;
                        }
                        case 4: {
                            sprintf(filename, "Sudoku_BIN-%02d.bin", b);
                            b++;
                            WritePuzzleInFileBIN(&sudoku, filename);
                            break;
                        }
                        case 0: printf("Voltar!\n");
                            break;
                        default: printf("Escolha invalida!\n");
                            break;
                    }

                } while (choice2 != 0);

                break;
            }

            case 2: {
                SUDOKU sudoku={0, 0, NULL};
                col=0;
                lin=0;

                line_columns_from_txt(&col, &lin, FILENAME_MEDIO);
                char** matriz_sudoku=read_file_to_pointer(lin, col, FILENAME_MEDIO);
                create_array_tables(&sudoku, lin, col);
                insert_cel_into_table(&sudoku, matriz_sudoku);

                num_restantes = 81 - calc_num_restantes(&sudoku);

                print_sudoku(&sudoku);

                printf("\n");

                do
                {
                    printf("Escolha uma das opcoes:\n");
                    printf("1. ->Resolver Sudoku pelas Regras\n");
                    printf("2. ->Resolver Sudoku por BackTracking\n");
                    printf("3. ->Guardar Sudoku em Ficheiro de texto\n");
                    printf("4. ->Guardar Sudoku como Ficheiro Binario\n");
                    printf("\n0. Voltar para o Menu anterior\n");
                    scanf("%d",&choice2);

                    switch(choice2)
                    {
                        case 1: {
                            ///RULES

                            printf("\n");
                            print_sudoku(&sudoku);
                            printf("\n");

                            while (num_restantes > 0) {
                                progress = checkPuzzle(&sudoku);
                                num_restantes--;
                                //printf("faltam %d numeros\n", num_restantes);
                                if (progress == 0) {
                                    //printf("Escolha a opcao 2. para resolver por BackTracking\n");
                                    break;
                                }
                            }
                            print_sudoku(&sudoku);
                            break;
                        }
                        case 2: {
                            ///backtracking

                            printf("\n");
                            print_sudoku(&sudoku);
                            printf("\n");

                            solve_sudoku(&sudoku);
                            print_sudoku(&sudoku);
                            break;
                        }
                        case 3: {
                            sprintf(filename, "Sudoku_TXT-%02d.txt", k);
                            k++;
                            WritePuzzleInFileTXT(&sudoku, filename);
                            break;
                        }
                        case 4: {
                            sprintf(filename, "Sudoku_BIN-%02d.bin", b);
                            b++;
                            WritePuzzleInFileBIN(&sudoku, filename);
                            break;
                        }
                        case 0: printf("Voltar!\n");
                            break;
                        default: printf("Escolha invalida!\n");
                            break;
                    }

                } while (choice2 != 0);

                break;
            }
            case 3: {
                SUDOKU sudoku={0, 0, NULL};
                col=0;
                lin=0;

                line_columns_from_txt(&col, &lin, FILENAME_DIFICIL);
                char** matriz_sudoku=read_file_to_pointer(lin, col, FILENAME_DIFICIL);
                create_array_tables(&sudoku, lin, col);
                insert_cel_into_table(&sudoku, matriz_sudoku);

                num_restantes = 81 - calc_num_restantes(&sudoku);

                print_sudoku(&sudoku);

                printf("\n");

                do
                {
                    printf("Escolha uma das opcoes:\n");
                    printf("1. ->Resolver Sudoku pelas Regras\n");
                    printf("2. ->Resolver Sudoku por BackTracking\n");
                    printf("3. ->Guardar Sudoku em Ficheiro de texto\n");
                    printf("4. ->Guardar Sudoku como Ficheiro Binario\n");
                    printf("\n0. Voltar para o Menu anterior\n");
                    scanf("%d",&choice2);

                    switch(choice2)
                    {
                        case 1: {
                            ///RULES

                            printf("\n");
                            print_sudoku(&sudoku);
                            printf("\n");

                            while (num_restantes > 0) {
                                progress = checkPuzzle(&sudoku);
                                num_restantes--;
                                //printf("faltam %d numeros\n", num_restantes);
                                if (progress == 0) {
                                    //printf("Escolha a opcao 2. para resolver por BackTracking\n");
                                    break;
                                }
                            }
                            print_sudoku(&sudoku);
                            break;
                        }
                        case 2: {
                            ///backtracking

                            printf("\n");
                            print_sudoku(&sudoku);
                            printf("\n");

                            solve_sudoku(&sudoku);
                            print_sudoku(&sudoku);
                            break;
                        }
                        case 3: {
                            sprintf(filename, "Sudoku_TXT-%02d.txt", k);
                            k++;
                            WritePuzzleInFileTXT(&sudoku, filename);
                            break;
                        }
                        case 4: {
                            sprintf(filename, "Sudoku_BIN-%02d.bin", b);
                            b++;
                            WritePuzzleInFileBIN(&sudoku, filename);
                            break;
                        }
                        case 0: printf("Voltar!\n");
                            break;
                        default: printf("Escolha invalida!\n");
                            break;
                    }

                } while (choice2 != 0);

                break;
            }

            case 0: printf("Quitting program!\n");
                exit(0);
            default: printf("Invalid choice!\n");
                break;
        }

    } while (choice != 0);

}

/**
 * TEste de resoluçao do sudoku, mostrando as possibilidades de cada celula
 * @return
 */
int main_test_possibilities() {
    SUDOKU sudoku={0, 0, NULL};
    int col=0;
    int lin=0;
    int progress;
    line_columns_from_txt(&col, &lin, FILENAME_MEDIO);
    char** matriz_sudoku=read_file_to_pointer(lin, col, FILENAME_MEDIO);
    create_array_tables(&sudoku, lin, col);
    insert_cel_into_table(&sudoku, matriz_sudoku);
    print_sudoku(&sudoku);

    printf("\n");

    while (UNSOLVED > 0) {
        progress = checkPuzzle(&sudoku);
        printf("faltam %d numeros\n", UNSOLVED);
        if (progress == 0) {
            printf("falha ao resolver o sudoku pelas regras\n");
            break;
        }
    }

    print_sudoku_possibilities(&sudoku);
    printf("%d", UNSOLVED);



    return 0;

}
/**
 * teste de resoluçao do sudoku
 * @return
 */
int main_test2(){

    SUDOKU sudoku={0, 0, NULL};
    int col=0;
    int lin=0;
    int progress;
    line_columns_from_txt(&col, &lin, FILENAME);
    char** matriz_sudoku=read_file_to_pointer(lin, col, FILENAME);
    create_array_tables(&sudoku, lin, col);
    insert_cel_into_table(&sudoku, matriz_sudoku);
    print_sudoku(&sudoku);

    printf("\n");

    while (UNSOLVED > 0) {
        progress = checkPuzzle(&sudoku);
        printf("faltam %d numeros\n", UNSOLVED);
        if (progress == 0) {
            printf("Falha ao resolver o Sudoku pelas regras\n");
            break;
        }
    }

    ///backtracking
    //solve_sudoku(&sudoku);


    print_sudoku(&sudoku);



    printf("%d", UNSOLVED);


    return 0;
}

/**
 * TESTE apenas utilizando Backtracking
 * @return
 */
int main_test2_backtracking() {
    SUDOKU sudoku={0, 0, NULL};
    int col=0;
    int lin=0;

    line_columns_from_txt(&col, &lin, FILENAME_MEDIO);
    char** matriz_sudoku=read_file_to_pointer(lin, col, FILENAME_MEDIO);
    create_array_tables(&sudoku, lin, col);
    insert_cel_into_table(&sudoku, matriz_sudoku);
    print_sudoku(&sudoku);

    printf("\n");

    ///backtracking
    solve_sudoku(&sudoku);

    print_sudoku(&sudoku);

    printf("%d", UNSOLVED);

    return 0;
}
/**
 * Print Sudoku com possibilidades das celulas
 * @return
 */
void print_sudoku_possibilities(SUDOKU* s){
    for(int i=0; i<s->nlines; i++){
        printf("\t");
        SQUARE* sq=(s->ptable+i)->psquare;
        for(int j=0; j<s->ncol; j++){
            if(j==0)
                printf("| ");

            if(sq->number==0) {
                printf(". ");
                for (int x = 0; x < 9; x++) {
                    if(sq->possible[x] == 0)
                        printf("[%d]", x+1);

                }
            }
            else
                printf("%d ", sq->number);


            if((j+1)%3==0 )
                printf("| ");
            sq=sq->E;
        }
        if((i+1)%3==0 )
            printf("\n\t-------------------------");

        printf("\n");
    }
}


int calc_num_restantes(SUDOKU* s){
    int countnum=0;

    for(int i=0; i<s->nlines; i++){
        SQUARE* sq=(s->ptable+i)->psquare;
        for(int j=0; j<s->ncol; j++){

            if(sq->number!=0)
                countnum++;
            sq=sq->E;
        }
    }
    return countnum;
}