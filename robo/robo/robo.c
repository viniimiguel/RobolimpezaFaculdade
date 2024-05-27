#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#define ROWS 8
#define COLS 8

int x, y;
int dx, dy;

char matrix[ROWS][COLS] = {
    {'-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-'},
    {'-', '-', '-', '-', '-', '-', '-', '-'},
};

void printMatrix() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(" %c |", matrix[i][j]);
        }
        printf("\n");
    }
}

void robotEstation() {
    printf("Digite onde você quer a estaçao no eixo horizontal (0 a 7): ");
    scanf_s("%d", &x);
    printf("Digite onde você quer a estaçao no eixo vertical (0 a 7): ");
    scanf_s("%d", &y);
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS) {
        matrix[y][x] = 'E';
    }
    else {
        printf("Coordenadas fora do limite da matriz! ");
    }
    printMatrix();
}

void dirtyMatrix() {
    while (true) {
        int exit;
        printf("Digite onde voce quer colocar a sujeira (0 a 7) (eixo horizontal): ");
        scanf_s("%d", &dx);
        printf("Digite onde voce quer colocar a sujeira (0 a 7) (eixo vertical): ");
        scanf_s("%d", &dy);
        printf("Quer sair? Digite (-1) para SIM ou (0) para NÃO: ");
        scanf_s("%d", &exit);

        if (exit == -1) {
            break;
        }
        else if (dx >= 0 && dx < ROWS && dy >= 0 && dy < COLS) {
            if (matrix[dy][dx] != 'E') {
                matrix[dy][dx] = '#';
                system("cls");
                printMatrix();
            }
            else {
                printf("A coordenada e uma estaçao, digite novamente em outra coordenada.\n");
            }
        }
        else {
            printf("Coordenada invalida, tente novamente!\n");
        }
    }
}

bool moveRobot(int* rx, int* ry) {
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; 
    for (int d = 0; d < 4; d++) {
        int nx = *rx + directions[d][0];
        int ny = *ry + directions[d][1];
        if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && (matrix[ny][nx] == '#' || matrix[ny][nx] == 'E')) {
            if (matrix[*ry][*rx] != 'E') {
                matrix[*ry][*rx] = ' ';
            }
            *rx = nx;
            *ry = ny;
            if (matrix[ny][nx] == '#') {
                matrix[ny][nx] = '-';
            }
            return true;
        }
    }
    return false; 
}

void cleanDirty() {
    int rx = x, ry = y; 
    system("cls");
    printMatrix();

    while (true) {
        Sleep(1000);
        if (!moveRobot(&rx, &ry)) {
            break; 
        }
        matrix[ry][rx] = 'R'; 
        if (rx != x || ry != y) {
            matrix[y][x] = 'E';
        }
        system("cls");
        printMatrix();
    }

    matrix[y][x] = 'E';
    system("cls");
    printMatrix();
}

int main() {
    printMatrix();
    robotEstation();
    dirtyMatrix();
    cleanDirty();
    return 0;
}
