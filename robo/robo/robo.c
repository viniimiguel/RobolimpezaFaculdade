#include <stdio.h>
#include <stdbool.h>

#define ROWS 8
#define COLS 8

struct MatrixStruct {
    char matrix[ROWS][COLS];
};

typedef struct MatrixStruct MatrixStruct;

void printMatrix(MatrixStruct* mat) {
    printf("Matriz 8x8:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c | ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}

void addDirt(MatrixStruct* mat, int x, int y) {
    mat->matrix[x][y] = '#';
}

int main() {
    MatrixStruct mat;


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mat.matrix[i][j] = '-';
        }
    }

    printf("Caso não queira mais colocar sujeira, digite (-1, -1)\n");

    while (true) {
        int x, y;
        printf("Fileira: ");
        scanf_s("%d", &x);
        printf("Coluna: ");
        scanf_s("%d", &y);

        if (x == -1 || y == -1) {
            break;
        }

        
        if (x >= 0 && x < ROWS && y >= 0 && y < COLS) {
            addDirt(&mat, x, y);
        }
        else {
            printf("Coordenadas fora dos limites da matriz.\n");
        }
    }

    printMatrix(&mat);

    return 0;
}
