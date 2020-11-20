#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%i) " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)
#define log_matrix(M, ...) fprintf(stdout, "[MATRIX] (%s:%i) " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)

#define ROWS 0
#define COLUMNS 1
#define null NULL

enum calculations { MULT = 42, PLUS = 43, MINUS = 45 };

typedef struct {
    int position[2];
    int *matrix;
    int isNull;
} matrix_t;

int sort(char* src, int sizesrc, int* dest, int sizedest){
    int count = 0;
    for (int i = 0; i < sizesrc; i++){
        if (src[i] == MULT){
            dest[count++] = i;
        }
    }
    for (int i = 0; i < sizesrc; i++){
        if (src[i] != MULT){
            dest[count++] = i;
        }
    }
    free(src);
    return count > sizedest ? EXIT_SUCCESS : EXIT_FAILURE;
}

int multiply(matrix_t* matrix1, matrix_t* matrix2){
    log_info("**MULT**");
    if (matrix1->position[ROWS] != matrix2->position[COLUMNS] || matrix1->position[COLUMNS] != matrix2->position[ROWS]) { /*fprintf(stderr,*/log_info("Error: Chybny vstup!"); exit(100); }
    matrix_t mat;
    mat.position[ROWS] = matrix1->position[ROWS];
    mat.position[COLUMNS] = matrix2->position[COLUMNS];
    mat.matrix = (int*)calloc(matrix1->position[ROWS]*matrix2->position[COLUMNS], sizeof(int));
    mat.isNull = false;
    // int mat[matrix1->position[COLUMNS]][matrix2->position[ROWS]];
    log_info("mat.pos[%i][%i]", mat.position[ROWS], mat.position[COLUMNS]);
    if (mat.matrix == NULL) return EXIT_FAILURE;
    for(int i = 0; i < matrix1->position[ROWS]; ++i)
	{
		for(int j = 0; j < matrix2->position[COLUMNS]; ++j)
		{
			for(int k = 0; k < matrix1->position[COLUMNS]; ++k)
			{
				mat.matrix[i*mat.position[COLUMNS]+j] += matrix1->matrix[i*matrix1->position[COLUMNS]+k] * matrix2->matrix[k*matrix2->position[COLUMNS]+j];
			}
		}
	}
    matrix1->position[COLUMNS] = mat.position[COLUMNS];
    matrix1->position[ROWS] = mat.position[ROWS];
    matrix1->matrix = (int*)realloc(matrix1->matrix, matrix1->position[COLUMNS] * matrix1->position[ROWS] * sizeof(int));
    for(int k = 0; k < matrix1->position[ROWS]*matrix1->position[COLUMNS]; ++k){//НЕТРОГАЙ НАХУЙ ВСЕ АЛЛОКАЦИИ РАБОТАЮТ
		matrix1->matrix[k] = mat.matrix[k];
	}
    free(mat.matrix);
    matrix2->isNull = true;
    log_info("**MULT == DONE**");
    return EXIT_SUCCESS;
}

int add(matrix_t* matrix1, matrix_t* matrix2){
    log_info("++PLUS++");
    if (matrix1->position[ROWS] != matrix2->position[ROWS] || matrix1->position[COLUMNS] != matrix2->position[COLUMNS]) { /*fprintf(stderr,*/log_info("Error: Chybny vstup!"); exit(100); }
    for(int k = 0; k < matrix1->position[ROWS]; ++k){
        for(int i = 0; i < matrix1->position[COLUMNS]; ++i){
		    matrix1->matrix[k*matrix1->position[COLUMNS]+i] += matrix2->matrix[k*matrix2->position[COLUMNS]+i];
            // printf("%i ", matrix1->matrix[k*matrix1->position[COLUMNS]+i]);
        }
        // printf("\n");
	}
    matrix2->isNull = true;
    log_info("++PLUS == DONE++");
    return EXIT_SUCCESS;
}

int subtract(matrix_t* matrix1, matrix_t* matrix2){
    log_info("--MINUS--");
    if (matrix1->position[ROWS] != matrix2->position[ROWS] || matrix1->position[COLUMNS] != matrix2->position[COLUMNS]) { /*fprintf(stderr,*/log_info("Error: Chybny vstup!"); exit(100); }
    for(int k = 0; k < matrix1->position[ROWS]; ++k){
        for(int i = 0; i < matrix1->position[COLUMNS]; ++i){
		    matrix1->matrix[k*matrix1->position[COLUMNS]+i] -= matrix2->matrix[k*matrix2->position[COLUMNS]+i];
            // printf("%i ", matrix1->matrix[k*matrix1->position[COLUMNS]+i]);
        }
        // printf("\n");
	}
    matrix2->isNull = true;
    log_info("--MINUS == DONE--");
    return EXIT_SUCCESS;
}

void readMatrix(matrix_t *matrix, int q){
    for (int i = 0; i < matrix->position[ROWS] * matrix->position[COLUMNS]; i++)
        scanf("%i", &matrix->matrix[i]);
}

void printMatrix(matrix_t *matrix){
    printf("MATRIX PRINT:\n");
    printf("%i %i\n", matrix->position[ROWS], matrix->position[COLUMNS]);
    for(int k = 0; k < matrix->position[ROWS]; ++k){
        for(int i = 0; i < matrix->position[COLUMNS]; ++i){
		    i == matrix->position[COLUMNS]-1 ? printf("%i\n", matrix->matrix[k*matrix->position[COLUMNS]+i]) : printf("%i ", matrix->matrix[k*matrix->position[COLUMNS]+i]);
        }
	}
}

void count(matrix_t* mat, int *order, char* calcs, int quant){
    int counter = 0;//use counter-1
    // log_info("%i\n", quant);
    while(++counter <= quant){
        log_info("COUNTER -> %i", counter-1);
        for (int i = counter-1; i < quant; log_info("TUT i==%i", ++i)){
            log_info("TUT i==%i", i);
            log_info("ZDES==%i", order[counter-1]);
            if (order[counter-1] == i){
                switch (calcs[order[counter-1]]){
                    case MULT:
                        for (int k = order[counter-1]; k >= 0; k--){
                            log_info("TUT k==%i, i==%i", k, i);
                            if (mat[k].isNull){ // checks if we've already used this matrix
                                continue;
                            } else { //if not
                                log_info("MULT**");
                                log_info("[POS] -> %i %i", k, i+1);
                                log_info("[DIM1] -> %i x %i", mat[k].position[ROWS], mat[k].position[COLUMNS]);
                                log_info("[DIM2] -> %i x %i", mat[/*order[counter-1]*/i+1].position[ROWS], mat[/*order[counter-1]*/i+1].position[COLUMNS]);
                                multiply(&mat[k], &mat[i+1]);
                                break;
                            }
                        }
                        break;
                    case PLUS:
                        for (int k = order[counter-1]; k >= 0; k--){
                            // log_info("TUT k==%i, i==%i", k, i);
                            if (mat[k].isNull){ // checks if we've already used this matrix
                                continue;
                            } else { //if not
                                log_info("PLUS++");
                                log_info("[POS] -> %i %i", k, i+1);
                                log_info("[DIM1] -> %i x %i", mat[k].position[ROWS], mat[k].position[COLUMNS]);
                                log_info("[DIM2] -> %i x %i", mat[/*order[counter-1]*/i+1].position[ROWS], mat[/*order[counter-1]*/+1].position[COLUMNS]);
                                add(&mat[k], &mat[i+1]);
                                break;
                            }
                        }
                        break;
                    case MINUS:
                        for (int k = order[counter-1]; k >= 0; k--){
                            // log_info("TUT k==%i, i==%i", k, i);
                            if (mat[k].isNull){ // checks if we've already used this matrix
                                continue;
                            } else { //if not
                                log_info("MINUS--");
                                log_info("[POS] -> %i %i", k, i+1);
                                log_info("[DIM1] -> %i x %i", mat[k].position[ROWS], mat[k].position[COLUMNS]);
                                log_info("[DIM2] -> %i x %i", mat[/*order[counter-1]*/+1].position[ROWS], mat[/*order[counter-1]*/+1].position[COLUMNS]);
                                subtract(&mat[k], &mat[i+1]);
                                break;
                            }
                        }
                        break;
                    
                    default:
                        /*fprintf(stderr,*/log_info("Error: Chybny vstup!"); 
                        exit(100);
                }
                // i++;log_info("TUT i==%i", i);
            } else if (counter-1 < quant && order[counter-1] != order[quant-1]) {
                //как-то надо обнулить i если дошел до конца, но из order еще не последний элемент
                    
            } else {
                // i = 
            }
        }
        fprintf(stderr, "\n");
    }
    printMatrix(&mat[0]);
}

int main (){
    matrix_t *mat = calloc(100, sizeof(matrix_t));
    char *calcs = calloc(10, sizeof(char));
    int quant = 0;//-1 quantity of matrix (also quantity of calcs)
    // fprintf(stderr, "SIZE = %lu\n", sizeof(mat));

    if (mat == NULL){
        log_info("NULL");
        return 100;
    }
    if (calcs == NULL){
        log_info("NULL");
        return 100;
    }
    while(1){
        // fprintf(stderr, "Quant = %i\t", quant);
        int zz = scanf("%i%i", &mat[quant].position[ROWS], &mat[quant].position[COLUMNS]);
        mat[quant].matrix = calloc(mat[quant].position[ROWS] * mat[quant].position[COLUMNS], sizeof(int));
        if (mat[quant].matrix == NULL){
            log_info("NULL");
            mat[quant].isNull = true;
        } else mat[quant].isNull = false;
        if(zz != 2) break;
        // log_info("poses: %i | %i\n\n", mat[quant].position[ROWS], mat[quant].position[COLUMNS]);
        // log_matrix("Matrix size is -> %i", mat[quant].position[ROWS] * mat[quant].position[COLUMNS]);
        
        readMatrix(&mat[quant], quant);

        if (scanf("\n%c",&calcs[quant]) == EOF) break;
        // log_matrix("\n%c", calcs[quant]);
        quant++;
    }
    // printf("---------------------------------------\n");
    int order[quant];
    char* ncalcs = calloc(sizeof(calcs), sizeof(char));
    if (ncalcs == NULL){
        log_info("NULL");
        return 100;
    }
    
    strcpy(ncalcs, calcs);
    if (!sort(ncalcs, quant, order, quant)) { log_info("ERROR"); return 100; }
    // free(ncalcs);
    for (int i = 0; i < quant; i++)
    {
        log_matrix("%i", order[i]);
    }
    printf("\n");
    // log_matrix("%i", !mat[0].isNull);
    // mat[0].isNull = true;
    // log_matrix("%i", mat[0].isNull == true);
    count(mat, order, calcs, quant);
    // example: multiply(&mat[0], &mat[1]);
    // log_info("ERROR! %i", multiply(&mat[0], &mat[1]));
    // log_info("ERROR! %i", add(&mat[0], &mat[2]));
    // printMatrix(&mat[0]);

    for (int i = 0; i <= quant; i++)
        free(mat[i].matrix);
    free(mat);
    free(calcs);

    return 0;
}
