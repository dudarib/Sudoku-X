//
// Created by dudar on 10/12/2019.
//

#include "sudokuX.h"

int UNSOLVED = 81;

/**
 * funçao para guardar o numero de linhas e colunas do ficheiro de texto
 * no endereço de memoria de lin e col
 *
 * @param col - endereço de memória onde é guardado o numero de colunas
 * @param lin - endereço de memória onde é guardado o numero de linhas
 * @param filename - path para o ficheiro txt pretendido
 */
void line_columns_from_txt(int *col, int* lin, char* filename){
    FILE* fp;
    fp=fopen(filename, "r");
    char str[MAXSUDOKU];
    fgets(str, MAXSUDOKU, fp);
    for(int i=0; str[i]!='\n'; i++){
        *col+=1;
    }
    *lin=1;
    while(!feof(fp)){
        fgets(str, MAXSUDOKU, fp);
        *lin+=1;
    }
    fclose(fp);
}

/**
 *aloca espaço de acordo com as linhas e colunas necessarias. lê do
 * ficheiro de texto e guarda o tabuleiro num apontador de caracteres
 * ppaux
 *
 * @param lin - numero de linhas
 * @param col - numero de colunas
 * @param filename - path para o ficheiro txt pretendido
 * @return ppaux - apontador para matriz de caracteres
 */
char** read_file_to_pointer(int lin, int col, char* filename){
    FILE* fp;
    char* paux=NULL;
    char** ppaux=(char**) calloc((lin), sizeof(char*));
    for(int i=0; i<lin; i++){
        paux=(char*) calloc((col), sizeof(char));
        *(ppaux+i)=paux;
    }
    fp=fopen(filename, "r");
    char str[MAXSUDOKU];
    int k=0;
    while(!feof(fp)){
        fgets(str, MAXSUDOKU, fp);
        strcpy(*(ppaux+k), str);
        k++;
    }
    fclose(fp);
    return ppaux;
}
/**
 * Aloca espaço para a estrutura TABLE de acordo com as linhas necessarias
 * e inicializa as suas variaveis.
 *
 * @param ps - estrutura do SUDOKU
 * @param lines - numero de linhas necessarias
 * @param cols - numero de colunas necessarias
 */
void create_array_tables(SUDOKU* ps, int lines, int cols){
    ps->ptable=malloc(sizeof(TABLE)*lines);
    ps->nlines=lines;
    ps->ncol=cols;
    for(int i=0; i<lines; i++){
        (ps->ptable+i)->psquare=NULL;
        (ps->ptable+i)->line=i;
    }
}

/**
 * serve para iniciar e inserir na tabela, todas as células do sudoku, ou seja atribuir a cada
 * variavel os seus respetivos valores, de acordo com as restriçoes existentes no jogo.
 *
 * @param ps - estrutura do SUDOKU
 * @param matrix - apontador para onde está armanezada a matriz do sudoku
 */
void insert_cel_into_table(SUDOKU *ps, char** matrix){

    int currentBox= 0;

    for(int i=0; i<ps->nlines; i++){
        TABLE* table_aux=(ps->ptable+i);
        for(int j=0; j<ps->ncol; j++){
            SQUARE* square_aux=table_aux->psquare;
            SQUARE* square_temp=malloc(sizeof(SQUARE));
            square_temp->N=NULL;
            square_temp->NE=NULL;
            square_temp->E=NULL;
            square_temp->SE=NULL;
            square_temp->S=NULL;
            square_temp->SO=NULL;
            square_temp->O=NULL;
            square_temp->NO=NULL;
            square_temp->number=*(*(matrix+i)+j)-48;
            square_temp->row = i;
            square_temp->column = j;
            square_temp->solvable=9;

            square_temp->box = currentBox;

            if(j == 2){
                currentBox++;
            }
            if(j == 5){
                currentBox++;
            }

            //inicializa os possiveis a 0
            for (int x = 0;  x < SIZE ; x++) {
                square_temp->possible[x] = 0;
            }
            connect(ps, square_temp, square_aux, i, j);
        }
        currentBox-=2;
        if(i ==2)
            currentBox = 3;
        if(i ==5)
            currentBox = 6;
    }

    /* loop linhas */
    for (int i = 0;  i< ps->nlines ; i++) {
        SQUARE* sq=(ps->ptable+i)->psquare;
        /* loop colunas */
        for (int j = 0; j < ps->ncol; j++) {

            if(sq->number != 0){
                sq->solvable = 0;
                updateSudoku(ps, sq, sq->row, sq->column);

                UNSOLVED--;
            }
            sq=sq->E;
        }
    }
}

/**
 * conecta as células de forma a criarem uma matriz de células em que
 * cada célula fica a apontar para as suas células vizinhas na matriz
 *
 * @param ps - estrutura do SUDOKU
 * @param cel_temp - nova célula a adicionar
 * @param cel_aux - célula auxiliar, que inicialmente aponta para a primeira célula da linha
 * @param i - posiçao na linha da nova célula (cel_temp)
 * @param j - posiçao na coluna da nova célula (cel_temp)
 */
void connect(SUDOKU* ps, SQUARE* cel_temp, SQUARE* cel_aux, int i, int j){
    if(i==0){
        if(ps->ptable->psquare==NULL){  ///caso seja a primeira celula
            ps->ptable->psquare=cel_temp;
            return;
        }
        while(cel_aux->E!=NULL){        ///andar com o cell aux para a direita
            cel_aux=cel_aux->E;
        }
        cel_aux->E=cel_temp;        ///apontar para a celula da esquerda e direita
        cel_temp->O=cel_aux;
        return;
    }
    if(j==(ps->ncol)-1){
        while(cel_aux->E!=NULL){
            cel_aux=cel_aux->E;
        }
        cel_aux->E=cel_temp;
        cel_temp->O=cel_aux;
        cel_aux=cel_aux->N;
        cel_temp->NO=cel_aux;
        cel_aux->SE=cel_temp;
        cel_aux=cel_aux->E;
        cel_temp->N=cel_aux;
        cel_aux->S=cel_temp;
        return;
    }
    if((ps->ptable+i)->psquare==NULL){      /// caso a primeira celula da linha esteja a null
        (ps->ptable+i)->psquare=cel_temp;
        cel_temp->N=(ps->ptable+(i-1))->psquare;
        cel_temp->NE=(ps->ptable+(i-1))->psquare->E;     //
        (ps->ptable+(i-1))->psquare->S=cel_temp;        /// ligar a celula de cima á de baixo
        (ps->ptable+(i-1))->psquare->E->SO=cel_temp;
        return;
    }
    while(cel_aux->E!=NULL){
        cel_aux=cel_aux->E;
    }
    cel_aux->E=cel_temp;
    cel_temp->O=cel_aux;
    cel_aux=cel_aux->N;
    cel_temp->NO=cel_aux;
    cel_aux->SE=cel_temp;
    cel_aux=cel_aux->E;
    cel_temp->N=cel_aux;
    cel_aux->S=cel_temp;
    cel_aux=cel_aux->E;
    cel_temp->NE=cel_aux;
    cel_aux->SO=cel_temp;
}

/**
 * funçao que imprime o sudoku
 *
 * @param s - estrutura do SUDOKU
 */
void print_sudoku(SUDOKU* s){
    for(int i=0; i<s->nlines; i++){
        printf("\t");
        SQUARE* sq=(s->ptable+i)->psquare;
        for(int j=0; j<s->ncol; j++){
            if(j==0)
                printf("| ");

            if(sq->number==0)
                printf(". ");

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

///SOLVE BY RULES


/**
 * funçao para utilizar as estratégias para resolver o sudoku
 *
 * @param s - estrutura do SUDOKU
 * @return 1 caso tenha sucesso, e 0 caso não consiga utilizar nenhuma das estrategias
 */
int checkPuzzle(SUDOKU* s){
    int i;

    for(i=0; i<s->nlines; i++) {
        SQUARE *sq = (s->ptable + i)->psquare;
        while (sq->E != NULL) {
            if (sq->solvable == 1) {
                solveSquare(sq);
                updateSudoku(s, sq, sq->row, sq->column);

                return 1;
            }
            sq = sq->E;
        }
    }

   //check se tem algum single na box e atualiza o numero da celula, e remove as
   // possibilidades com esse num das celulas da mesma linha coluna e diagonal principal
    if (rowHiddenAloneNumber(s)) {
        //printf("ROWhiddenAloneNum");
        return 1;
    }

    if (colHiddenAloneNumber(s)) {
        //printf("COLhiddenAloneNum");
        return 1;
    }

    if (boxHiddenAloneNumber(s)) {
        //printf("BOXhiddenNum");
        return 1;
    }

    /*
   if (boxAlonePairs(s)) {
       printf("alonepairBOX");
       return 1;
   }
    */


   if (checkRows(s)) {
       //printf("check rows");
       return 1;
   }

   if (checkColumns(s)) {
       //printf("check columns");
       return 1;
   }

    return 0;

}

/**
 *serve para atualizar o array de possiveis de um numero passado na funçao de cada
 * célula que se encontre na mesma linha, coluna, submatriz, e/ou diagonal
 * secundária e principal
 *
 * @param s - estrutura do SUDOKU
 * @param cel - célula do tipo SQUARE, serve para obtermos o numero em questao
 * @param row - linha da célula
 * @param col - coluna da célula
 * @return 1 caso tenha sucesso
 */
int updateSudoku(SUDOKU* s, SQUARE* cel, int row, int col){
    int i,j;
    int number = cel->number;
    SQUARE *sq = (s->ptable + row)->psquare;
    SQUARE *fsq = (s->ptable)->psquare;

    ///verifica linha
    for(j=0; j<s->ncol; j++){
        if(sq->possible[number - 1] == 0){
            sq->solvable--;
        }
        sq->possible[number - 1] = 1;

        sq=sq->E;
    }


    ///verifica coluna
    for(i=0;i<col;i++){
        fsq=fsq->E;
    }
    for(j=0; j<s->ncol; j++){
        if(fsq->possible[number - 1] == 0){
            fsq->solvable--;
        }
        fsq->possible[number - 1] = 1;
        fsq=fsq->S;
    }


    //verifica diagonal principal
    if(row == col) {

        fsq = (s->ptable)->psquare;
        for(j=0; j<s->ncol; j++){
            if(fsq->possible[number - 1] == 0){
                fsq->solvable--;
            }
            fsq->possible[number - 1] = 1;
            fsq = fsq->SE;
        }
    }


    //verifica diagonal secundaria
    if ((row + col) == (SIZE - 1)) {

        fsq = (s->ptable)->psquare;
        while (fsq->E != NULL) {
            fsq = fsq->E;
        }
        for(j=0; j<s->ncol; j++){
            if(fsq->possible[number - 1] == 0){
                fsq->solvable--;
            }
            fsq->possible[number - 1] = 1;
            fsq = fsq->SO;
        }
    }

    //verifica submatriz
    int row_start = (row/3)*3;
    int col_start = (col/3)*3;

    for(i=row_start; i<row_start+3; i++){
        fsq=(s->ptable+i)->psquare;
        while(fsq->column < col_start){
            fsq = fsq->E;
        }

        for(j=col_start; j<col_start+3; j++){
            if(fsq->possible[number - 1] == 0){
                fsq->solvable--;
            }
            fsq->possible[number - 1] = 1;
            fsq=fsq->E;
        }

    }



    return 1;
}
/**
 * coloca o unico numero possivel na célula passada por parametro, e atualiza
 * o numero de possiveis para 0
 *
 * @param cel - célula do tipo SQUARE
 * @return 1
 */
int solveSquare(SQUARE* cel){

    int x;
    for (x = 0;  x < SIZE; x++) {

        if(cel->possible[x] == 0){
            cel->number = x+1;
            cel->solvable = 0;
            UNSOLVED--;
        }
    }
    return 1;
}

///ESTRATEGIAS

/**
 * Estratégia para perceber se uma célula numa submatriz do sudoku tiver um numero possivel,
 * que nao existe em mais nenhuma célula da mesma submatriz, é porque esse numero é o unico
 * possivel nessa célula da submatriz e adiciona esse numero possivel na célula e faz um
 * update às restantes células na mesma linha, coluna, submatriz e diagonais que esse numero
 * adicionado ja nao é possivel nos seus arrays de possiveis
 *
 * @param s - estrutura do SUDOKU
 * @return 1 caso tenha resolvido alguma célula e 0 caso não tenha resolvido nada
 */
int boxHiddenAloneNumber(SUDOKU* s){
    int i, j, k, box;
    int count=0, countbox=0;
    int temprow=0;
    int tempcol=0;


    //loop boxes
    for (box = 0; box < 9; box++) {

        for(i=0; i<s->nlines; i++) {
            SQUARE *sq = (s->ptable + i)->psquare;
            for(int x=0; x < s->ncol; x++){

                if(sq->box == box){
                    box++;

                    /**
                     * @param k - percorre todas as possibilidades
                     */
                    for (k = 0;  k < 9; k++) {
                        count = 0;

                        ///percorrer submatriz
                        int row_start = (sq->row / 3) * 3;
                        int col_start = (sq->column / 3) * 3;

                        for (i = row_start; i < row_start + 3; i++) {
                            if(count == 2)
                                break;
                            SQUARE *sqsm = (s->ptable + i)->psquare;
                            while (sqsm->column < col_start) {
                                sqsm = sqsm->E;
                            }

                            for (j = col_start; j < col_start + 3; j++) {
                                if (sqsm->number != 0){
                                    sqsm = sqsm->E;
                                    continue;
                                }
                                //verificar se o numero que estamos a ver é possivel ali
                                if (sqsm->possible[k] == 0) {
                                    count++;
                                    temprow = sqsm->row;
                                    tempcol = sqsm->column;
                                }
                                if (count == 2)
                                    break;

                                sqsm = sqsm->E;
                            }

                        }
                        if (count == 1) {
                            SQUARE *sqsm = (s->ptable + temprow)->psquare;
                            while (sqsm->column < tempcol) {
                                sqsm = sqsm->E;
                            }
                            sqsm->number = k + 1;
                            UNSOLVED--;
                            sqsm->solvable = 0;

                            //atualizar as linhas , colunas e diag para saber que este numero ja nao é possivel nas linhas , colunas e diag correspondentes
                            updateSudoku(s, sqsm, sqsm->row, sqsm->column);

                            //retorno 1 para saber se atualizou algum numero
                            return 1;
                        }
                    }

                }

                sq = sq->E;
            }
        }
    }

    //caso nao tenha resolvido nada
    return 0;
}

/**
 * Estratégia para perceber se uma célula numa coluna do sudoku tiver um numero possivel,
 * que nao existe em mais nenhuma célula da mesma coluna, é porque esse numero é o unico
 * possivel nessa célula da submatriz e adiciona esse numero possivel na célula e faz um
 * update às restantes células na mesma linha, coluna, submatriz e diagonais que esse numero
 * adicionado ja nao é possivel nos seus arrays de possiveis
 *
 * @param s - estrutura do SUDOKU
 * @return 1 caso tenha resolvido alguma célula e 0 caso não tenha resolvido nada
 */
int colHiddenAloneNumber(SUDOKU* s) {
    int i, j, k;
    int count = 0;
    int temprow = 0;
    int tempcol = 0;

    SQUARE *sqcol;
    SQUARE *fsq = (s->ptable)->psquare;

    //loop por todas as colunas
    for (j = 0; j < s->ncol; j++) {

        /**
         * @param k - percorre todas as possibilidades
         */
        for (k = 0; k < 9; k++) {
            count = 0;
            sqcol = fsq;

            //loop cada quadrado da coluna
            for (i = 0; i < s->ncol; i++) {
                if (sqcol->number != 0) {
                    sqcol = sqcol->S;
                    continue;
                }
                //verificar se o numero que estamos a ver é possivel ali
                if (sqcol->possible[k] == 0) {
                    count++;
                    temprow = sqcol->row;
                    tempcol = sqcol->column;
                }
                if (count == 2)
                    break;

                sqcol = sqcol->S;

            }
            if (count == 1) {
                SQUARE *sqsm = (s->ptable + temprow)->psquare;
                while (sqsm->column < tempcol) {
                    sqsm = sqsm->E;
                }
                sqsm->number = k + 1;
                UNSOLVED--;
                sqsm->solvable = 0;

                //atualizar as linhas , colunas e diag para saber que este numero ja nao é possivel nas linhas , colunas e diag correspondentes
                updateSudoku(s, sqsm, sqsm->row, sqsm->column);

                //retorno 1 para saber se atualizou algum numero
                return 1;
            }
        }

        fsq = fsq->E;
    }
    return 0;
}

/**
 * Estratégia para perceber se uma célula numa coluna do sudoku tiver um numero possivel,
 * que nao existe em mais nenhuma célula da mesma coluna, é porque esse numero é o unico
 * possivel nessa célula da submatriz e adiciona esse numero possivel na célula e faz um
 * update às restantes células na mesma linha, coluna, submatriz e diagonais que esse numero
 * adicionado ja nao é possivel nos seus arrays de possiveis
 *
 * @param s - estrutura do SUDOKU
 * @return 1 caso tenha resolvido alguma célula e 0 caso não tenha resolvido nada
 */
int rowHiddenAloneNumber(SUDOKU* s) {
    int i, j, k;
    int count = 0;
    int temprow = 0;
    int tempcol = 0;

    for (k = 0; k < 9; k++) {
        count = 0;

        for (i = 0; i < s->nlines; i++) {
            SQUARE *sq = (s->ptable + i)->psquare;
            for (j = 0; j < s->ncol; j++) {
                if (sq->number != 0) {
                    sq = sq->E;
                    continue;
                }
                //verificar se o numero que estamos a ver é possivel ali
                if (sq->possible[k] == 0) {
                    count++;
                    temprow = sq->row;
                    tempcol = sq->column;
                }
                if (count == 2)
                    break;

                sq = sq->E;

            }
        }
        if (count == 1) {
            SQUARE *sqsm = (s->ptable + temprow)->psquare;
            while (sqsm->column < tempcol) {
                sqsm = sqsm->E;
            }
            sqsm->number = k + 1;
            UNSOLVED--;
            sqsm->solvable = 0;

            //atualizar as linhas , colunas e diag para saber que este numero ja nao é possivel nas linhas , colunas e diag correspondentes
            updateSudoku(s, sqsm, sqsm->row, sqsm->column);

            //retorno 1 para saber se atualizou algum numero
            return 1;
        }
    }
    return 0;
}

/*
int boxAlonePairs(SUDOKU* s){
    int i, j, k, box;
    int count=0;
    int temprow1=0, tempcol1=0, temprow2=0, tempcol2=0;
    int pair1=0, pair2=0;

    //loop boxes
    for (box = 0; box < 9; box++) {

        for(i=0; i<s->nlines; i++) {
            SQUARE *sq = (s->ptable + i)->psquare;
            while (sq->E != NULL) {

                if(sq->box == box){
                    box++;
                    count = 0;
                        ///percorrer submatriz
                        int row_start = (sq->row / 3) * 3;
                        int col_start = (sq->column / 3) * 3;

                        for (i = row_start; i < row_start + 3; i++) {
                            SQUARE *sqsm = (s->ptable + i)->psquare;
                            while (sqsm->column < col_start) {
                                sqsm = sqsm->E;
                            }

                            for (j = col_start; j < col_start + 3; j++) {
                                //percorre array possibilidades
                                for (k = 0; k < SIZE; k++) {

                                    if (sqsm->number != 0) {
                                        sqsm = sqsm->E;
                                        continue;
                                    }
                                    //se so tivermos dois numeros possiveis
                                    if (sqsm->solvable == 2) {
                                        //verificar se o numero que estamos a ver é possivel ali
                                        if (sqsm->possible[k] == 0) {
                                            count++;
                                            temprow2 = temprow1;
                                            tempcol2 = tempcol1;
                                            temprow1 = sqsm->row;
                                            tempcol1 = sqsm->column;
                                            pair2 = pair1;
                                            pair1 = k;
                                        }
                                    }

                                    if (count == 5)
                                        break;

                                    sqsm = sqsm->E;
                                }
                            }
                        }
                        if (count == 4) {

                            ///percorrer submatriz
                            row_start = (temprow1/ 3) * 3;
                            col_start = (tempcol2 / 3) * 3;

                            for (i = row_start; i < row_start + 3; i++) {

                                SQUARE *sqsm = (s->ptable + i)->psquare;
                                while (sqsm->column < col_start) {
                                    sqsm = sqsm->E;
                                }

                                for (j = col_start; j < col_start + 3; j++) {
                                        if (sqsm->number != 0) {
                                            sqsm = sqsm->E;
                                            continue;
                                        }
                                        if(sqsm->row == temprow1 && sqsm->column == tempcol1){
                                            sqsm = sqsm->E;
                                            continue;
                                        }
                                        if(sqsm->row == temprow2 && sqsm->column == tempcol2){
                                            sqsm = sqsm->E;
                                            continue;
                                        }
                                        for(k=0; k< SIZE; k++){
                                            if(sqsm->possible[k] == 0){
                                                if(k == pair1 || k == pair2){
                                                    sqsm->possible[k] = 1;
                                                    sqsm->solvable--;

                                                    //atualizar as linhas , colunas e diag para saber que este numero ja nao é possivel nas linhas , colunas e diag correspondentes
                                                    updateSudoku(s, sqsm, sqsm->row, sqsm->column);

                                                    //retorno 1 para saber se atualizou algum numero
                                                    return 1;
                                                }
                                            }
                                        }

                                        sqsm = sqsm->E;
                                }
                            }

                        }
                }

                sq = sq->E;
            }
        }
    }

    //caso nao tenha resolvido nada
    return 0;
}
*/

/**
 * Estratégia para verificar se um numero numa linha é o unico possivel
 * @param s - estrutura do SUDOKU
 * @return 1 se resolver, e 0 caso nao resolva
 */
int checkRows(SUDOKU* s){
    int i, j, k;
    int sum[9];
    int place[9];

    for(i=0; i<s->nlines; i++) {
        SQUARE *sq = (s->ptable + i)->psquare;

        //iniciar as posiçoes de sum e place a 0
        for (j = 0; j < 9; j++) {
            sum[j] = 0;
            place[j] = 0;
        }

        for(int x=0; x < s->ncol; x++){
            if(sq->number != 0){
                sq = sq->E;
                continue;
            }
            for (k = 0; k < 9; k++) {

                //verifica se o numero(k) é possivel
                if(sq->possible[k] == 0){
                    sum[k]++;
                    place[k] = sq->column;
                }

            }
            sq = sq->E;
        }

        for (k = 0; k < 9; k++) {
            if(sum[k] == 1){
                SQUARE *sqsm = (s->ptable + i)->psquare;
                while (sqsm->column < place[k]) {
                    sqsm = sqsm->E;
                }
                sqsm->number = k + 1;
                sqsm->solvable = 0;
                UNSOLVED--;
                //printf("%dcr", sqsm->number);
                updateSudoku(s, sqsm, sqsm->row, sqsm->column);

                return 1;
            }
        }

    }

    return 0;
}

/**
 * Estratégia para verificar se um numero numa coluna é o unico possivel
 * @param s - estrutura do SUDOKU
 * @return 1 se resolver, e 0 caso nao resolva
 */
int checkColumns(SUDOKU* s){
    int i, j, k;
    int sum[9];
    int place[9];

    SQUARE *sqcol;
    SQUARE *fsq = (s->ptable)->psquare;

    //loop por todas as colunas
    for(int x = 0; x < s->ncol; x++){
        sqcol = fsq;

        //iniciar as posiçoes de sum e place a 0
        for (j = 0; j < 9; j++) {
            sum[j] = 0;
            place[j] = 0;
        }

        //loop cada quadrado da coluna
        for(int q=0; q < s->ncol; q++){
            if(sqcol->number != 0){
                sqcol = sqcol->S;
                continue;
            }
            for (k = 0; k < 9; k++) {

                //verifica se o numero(k) é possivel
                if(sqcol->possible[k] == 0){
                    sum[k]++;
                    place[k] = sqcol->row;
                }

            }

            sqcol=sqcol->S;
        }
        for (k = 0; k < 9; k++) {
            if(sum[k] == 1){
                SQUARE *sqsm = (s->ptable + place[k])->psquare;
                while (sqsm->column < x) {
                    sqsm = sqsm->E;
                }
                sqsm->number = k + 1;
                sqsm->solvable = 0;
                UNSOLVED--;

                updateSudoku(s, sqsm, sqsm->row, sqsm->column);

                return 1;
            }
        }
        fsq=fsq->E;
    }
    return 0;
}


/**
 * escreve o sudoku para um ficheiro TXT
 *
 * @param s - estrutura do SUDOKU
 * @param filename - path onde quer guardar o ficheiro txt
 */void WritePuzzleInFileTXT(SUDOKU* s, char *filename)
{
    FILE *matrixtxt = fopen(filename, "w");

    for(int i=0; i<s->nlines; i++){
        SQUARE* sq=(s->ptable+i)->psquare;
        for(int j=0; j<s->ncol; j++){
            if(sq->number!=0)
                fprintf(matrixtxt,"%d",sq->number);
            else
                fprintf(matrixtxt,"0");

            sq=sq->E;
        }
        fprintf(matrixtxt,"\n");
    }

    fclose(matrixtxt);
    printf("Guardado como: %s \n", filename);
}


/**
 * escreve o sudoku para um ficheiro BIN
 *
 * @param s - estrutura do SUDOKU
 * @param filename - path onde quer guardar o ficheiro bin
 */
void WritePuzzleInFileBIN(SUDOKU* s, char *filename){

    FILE *fptr;
    if ((fptr = fopen(filename,"wb")) == NULL){
        printf("Erro a abrir ficheiro");
        exit(1);
    }
    for(int i=0; i<s->nlines; i++){
        SQUARE* sq=(s->ptable+i)->psquare;
        for(int j=0; j<s->ncol; j++){
            fputc(sq->number, fptr);
            sq=sq->E;
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    printf("Guardado como: %s \n", filename);
}