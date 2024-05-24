	#include <stdio.h>
	#include <stdbool.h>
	#include <Windows.h>
	#define ROWS 8
	#define COLS 8
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
				printf(" ");
				printf("%c", matrix[i][j]);
				printf(" ");
				printf("|");
			}
			printf("\n");
		}
	}

	int robotEstation() {
		int x, y;
		printf("digite onde voce quer a estacão no eixo horizontal digite apenas de 0 a 7: ");
		scanf_s("%d", &x);
		printf("digite onde voce quer a estacão no eixo vertical digite apenas de 0 a 7: ");
		scanf_s("%d", &y);
		if (x >= 0 && x <= ROWS && y >= 0 && y <= COLS) {
			matrix[y][x] = 'E';
		}
		else {
			printf("coordenadas fora do limite da matriz! ");
		}
		printMatrix();
	}
	void dirtyMatrix() {
		while (true) {
			int exit;
			printf("digite onde voce quer colocar a sujeira apenas de 0 a 7 (eixo horizontal) : ");
			scanf_s("%d", &dx);
			printf("digite onde voce quer colocar a sujeira de 0 a 7 (eixo vertical) :");
			scanf_s("%d", &dy);
			printf("Quer sair? digite (-1) para (SIM) ou (0) para (NAO): ");
			scanf_s("%d", &exit);

			if (exit == -1) {
				break;
			}
			else if (dx >= 0 && dx <= ROWS && dy >= 0 && dy <= COLS) {
				if (matrix[dy][dx] != 'E') {
					matrix[dy][dx] = '#';
					printMatrix();
				}
				else {
					printf("a coordenada e uma estacao digite novamente em outra coordenada.");
				}
			
			}
			else {
				printf("coordenada invalida tente novamente!!");
			}
		}
	}
	void cleanDirty() {

	}

	int main() {
		printMatrix();
		robotEstation();
		dirtyMatrix();
		return 0;
	}