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
void execStartPoint(MatrixStruct* mat, int startX, int startY)
{
    mat->matrix[startX][startY] = 'E';
}
int addStartPointX() {
    int startX;
    bool control = false;
    while (!control)
    {
        printf("qual sera o ponto de partida?\n");
        printf("coluna: ");
        scanf_s("%d", &startX);
        if (startX >= 0 && startX < ROWS) {
            break;
        }
        else {
            printf("Coordenadas fora dos limites da matriz.\n");
        }

    }

    return startX;
}

int addStartPointY() {
    int startY;
    bool control = false;
    while(!control)
    {
	    printf("fileira: ");
	    scanf_s("%d", &startY);
        if (startY >= 0 && startY < ROWS) {
            break;
        }
        else {
            printf("Coordenadas fora dos limites da matriz.\n");
        }
    }

    return startY;
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


    int startX = addStartPointX();
    int startY = addStartPointY();

    execStartPoint(&mat, startX, startY);


    printf("Caso nao queira mais colocar sujeira, digite (-1, -1)\n");

    while (true) {
        int x, y;
        printf("coluna: ");
        scanf_s("%d", &x);
        printf("fileira: ");
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