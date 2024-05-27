#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#define ROWS 8
#define COLS 8

int x, y; // Coordenadas da estação
int dx, dy; // Coordenadas temporárias para a sujeira

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
    printf("Digite onde você quer a estação no eixo horizontal (0 a 7): ");
    scanf_s("%d", &x);
    printf("Digite onde você quer a estação no eixo vertical (0 a 7): ");
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
        printf("Digite onde você quer colocar a sujeira (0 a 7) (eixo horizontal): ");
        scanf_s("%d", &dx);
        printf("Digite onde você quer colocar a sujeira (0 a 7) (eixo vertical): ");
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
                printf("A coordenada é uma estação, digite novamente em outra coordenada.");
            }
        }
        else {
            printf("Coordenada inválida, tente novamente!");
        }
    }
}

bool moveRobot(int* rx, int* ry) {
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; 
    for (int d = 0; d < 4; d++) {
        int nx = *rx + directions[d][0];
        int ny = *ry + directions[d][1];
        if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && matrix[ny][nx] == '#') {
            matrix[*ry][*rx] = '-';
            *rx = nx;
            *ry = ny;
            return true;
        }
    }
    return false;
}

void cleanDirty() {
    int rx = x, ry = y; 
    matrix[ry][rx] = 'R';
    system("cls");
    printMatrix();

    while (true) {
        Sleep(1000); 
        if (!moveRobot(&rx, &ry)) {
            break; 
        }
        system("cls");
        printMatrix();
    }
    matrix[ry][rx] = 'E';
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
