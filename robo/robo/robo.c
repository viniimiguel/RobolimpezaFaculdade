#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define ROWS 8
#define COLS 8

//horas gastas no codigo: 10;
//total de canecas de cafe: 9; << eu odeio cafe...

struct MatrixStruct {
    char matrix[ROWS][COLS];
};

typedef struct MatrixStruct MatrixStruct;

struct DirtCell {
    int x;
    int y;
};

typedef struct DirtCell DirtCell;

struct ActualPosition
{
    int x;
    int y;
};

typedef struct ActualPosition ActualPosition;

void printMatrix(MatrixStruct* mat) {
    printf("Matriz 8x8:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c | ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}

void execStartPoint(MatrixStruct* mat, int startX, int startY) {
    mat->matrix[startX][startY] = 'E';
}

int addStartPointX() {
    int startX;
    bool control = false;
    while (!control) {
        printf("Qual sera o ponto de partida?\n");
        printf("Coluna: ");
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
    while (!control) {
        printf("Fileira: ");
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

void matrixDryMap(MatrixStruct* mat, DirtCell* dirtCells, int* numDirt) {
    *numDirt = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (mat->matrix[i][j] == '#') {
                dirtCells[*numDirt].x = i;
                dirtCells[*numDirt].y = j;
                (*numDirt)++;
            }
        }
    }
}

void cleanDirt(MatrixStruct* mat, DirtCell* dirtCells, int numDirt) {
    ActualPosition robotPosition;
    robotPosition.x = dirtCells[0].x;
    robotPosition.y = dirtCells[0].y;

    for (int i = 0; i < numDirt; i++) {
        int nextX = dirtCells[i].x;
        int nextY = dirtCells[i].y;

        while (robotPosition.y != nextY) {
            mat->matrix[robotPosition.x][robotPosition.y] = '-';
            printMatrix(mat);
            if (robotPosition.y < nextY) {
                robotPosition.y++;
            }
            else {
                robotPosition.y--;
            }
            mat->matrix[robotPosition.x][robotPosition.y] = '@';
            printMatrix(mat);

           
#ifdef _WIN32
            Sleep(2000);
#else
            sleep(2); 
#endif
        }

        while (robotPosition.x != nextX) {
            mat->matrix[robotPosition.x][robotPosition.y] = '-';
            printMatrix(mat);
            if (robotPosition.x < nextX) {
                robotPosition.x++;
            }
            else {
                robotPosition.x--;
            }
            mat->matrix[robotPosition.x][robotPosition.y] = '@';
            printMatrix(mat);

#ifdef _WIN32
            Sleep(2000);
#else
            sleep(2);
#endif
        }
    }

    mat->matrix[robotPosition.x][robotPosition.y] = '-';
    printMatrix(mat);
}


void actualPosition(MatrixStruct* mat)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (mat->matrix[i][j] == '@')
            {
                printf("o robo se encontra em (%d, %d)", i, j);
                break;
            }
        }
    }
}
void returnToPosition(MatrixStruct* mat, int startX, int startY, int endX, int endY) {

}

int main() {
    MatrixStruct mat;
    DirtCell dirtCells[ROWS * COLS];
    int numDirt = 0;

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
        printf("Coluna: ");
        scanf_s("%d", &x);
        printf("Fileira: ");
        scanf_s("%d", &y);
        printf("---------------\n");

        if (x == -1 || y == -1) {
            break;
        }

        if (x >= 0 && x < ROWS && y >= 0 && y < COLS) {
            addDirt(&mat, x, y);
            printMatrix(&mat);

        }
        else {
            printf("Coordenadas fora dos limites da matriz.\n");
        }
    }

    printMatrix(&mat);

    matrixDryMap(&mat, dirtCells, &numDirt);
    printf("Posicoes com sujeira:\n");
    for (int i = 0; i < numDirt; i++) {
        printf("(%d, %d)\n", dirtCells[i].x, dirtCells[i].y);
    }

    cleanDirt(&mat, dirtCells, numDirt);
    actualPosition(&mat);
    printf("Matriz apos limpeza:\n");
    printMatrix(&mat);


    return 0;
}