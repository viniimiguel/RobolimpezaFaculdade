#include <stdio.h>
#include <stdbool.h>

#define ROWS 8
#define COLS 8

struct MatrixStruct {
    char matrix[ROWS][COLS];
    int x;
    int y;
};

// Definindo um apelido para a struct
typedef struct MatrixStruct MatrixStruct; 

void printMatrix(MatrixStruct* mat) {
    printf("Matriz 8x8:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c || ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}

void choiceDry(MatrixStruct* mat, int x, int y) {
    mat->matrix[x][y] = '#';
}

int main() {
    bool control = false;
    MatrixStruct mat;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mat.matrix[i][j] = '-';
        }
    }

    printf("Caso não queira mais colocar sujeira, digite (-1, -1)\n");

   
   

    
    printMatrix(&mat);

    return 0;
}
