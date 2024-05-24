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
    printf("Qual sera o ponto de partida (coluna)?: ");
    scanf_s("%d", &startX);
    return startX;
}

int addStartPointY() {
    int startY;
    printf("Qual sera o ponto de partida (fileira)?: ");
    scanf_s("%d", &startY);
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

#define MAX_SIZE ROWS * COLS

struct Stack {
    ActualPosition items[MAX_SIZE];
    int top;
};

typedef struct Stack Stack;

void initializeStack(Stack* stack) {
    stack->top = -1;
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, ActualPosition item) {
    if (!isFull(stack)) {
        stack->items[++stack->top] = item;
    }
}

ActualPosition pop(Stack* stack) {
    ActualPosition item = { -1, -1 };
    if (!isEmpty(stack)) {
        item = stack->items[stack->top--];
    }
    return item;
}

bool isValidPosition(MatrixStruct* mat, int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

bool isDirt(MatrixStruct* mat, int x, int y) {
    return mat->matrix[x][y] == '#';
}

void cleanDirt(MatrixStruct* mat, DirtCell* dirtCells, int numDirt, int startX, int startY) {
    ActualPosition robotPosition;
    robotPosition.x = startX;
    robotPosition.y = startY;

    Stack path;
    initializeStack(&path);

    for (int i = 0; i < numDirt; i++) {
        int nextX = dirtCells[i].x;
        int nextY = dirtCells[i].y;

        // Se a sujeira estiver em uma posição inacessível, ignorar
        if ((abs(robotPosition.x - nextX) + abs(robotPosition.y - nextY)) > 1) {
            continue;
        }

        // Limpar a sujeira
        mat->matrix[nextX][nextY] = '-';
        push(&path, robotPosition);
        mat->matrix[nextX][nextY] = '@';
        printMatrix(mat);
        Sleep(2000);

        robotPosition.x = nextX;
        robotPosition.y = nextY;
    }

    // Limpar o caminho de volta para a posição inicial
    while (!isEmpty(&path)) {
        ActualPosition prevPosition = pop(&path);
        mat->matrix[robotPosition.x][robotPosition.y] = '-';
        robotPosition.x = prevPosition.x;
        robotPosition.y = prevPosition.y;
        mat->matrix[robotPosition.x][robotPosition.y] = '@';
        printMatrix(mat);
        Sleep(2000);
    }
}

void actualPosition(MatrixStruct* mat)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (mat->matrix[i][j] == '@')
            {
                printf("O robo se encontra em (%d, %d)\n", i, j);
                return;
            }
        }
    }
}

void returnToPosition(MatrixStruct* mat, int startX, int startY, int lastPositionX, int lastPositionY) {
    ActualPosition robotPosition;
    robotPosition.x = lastPositionX;
    robotPosition.y = lastPositionY;

    while (robotPosition.x != startX || robotPosition.y != startY) {
        mat->matrix[robotPosition.x][robotPosition.y] = '@';
        if (robotPosition.x < startX) {
            robotPosition.x++;
        }
        else if (robotPosition.x > startX) {
            robotPosition.x--;
        }
        if (robotPosition.y < startY) {
            robotPosition.y++;
        }
        else if (robotPosition.y > startY) {
            robotPosition.y--;
        }
        mat->matrix[robotPosition.x][robotPosition.y] = '-';
        printMatrix(mat);
        Sleep(1000);
    }

    mat->matrix[startX][startY] = '@';

    printMatrix(mat);
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

        if (x == startX && y == startY)
        {
            printf("Voce nao pode sujar a estacao.\n");
        }
        if (x == -1 || y == -1) {
            break;
        }

        if (x >= 0 && x < ROWS && y >= 0 && y < COLS && (x != startX || y != startY)) {
            addDirt(&mat, x, y);
            printMatrix(&mat);
        }
        else {
            printf("Coordenadas fora dos limites da matriz.\n");
        }
    }

    int v, h;
    printf("Qual foi a sua ultima posicao? (coluna, fileira): ");
    scanf_s("%d %d", &v, &h);
    printMatrix(&mat);

    matrixDryMap(&mat, dirtCells, &numDirt);
    printf("Posicoes com sujeira:\n");
    for (int i = 0; i < numDirt; i++) {
        printf("(%d, %d)\n", dirtCells[i].x, dirtCells[i].y);
    }

    cleanDirt(&mat, dirtCells, numDirt, startX, startY);
    actualPosition(&mat);
    printf("Matriz apos limpeza:\n");
    printMatrix(&mat);
    returnToPosition(&mat, startX, startY, v, h);

    return 0;
}
