#include <stdio.h>


void printMatrix(char matrix[8][8])
{
	printf("matriz 8x8: \n");
	for(int i = 0;i < 8;i++)
	{
		for(int j = 0; j < 8;j++)
		{
			printf("%c || ", matrix[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	char matrix[8][8];
	for(int i=0;i < 8; i++)
	{
		for(int j=0;j < 8; j++)
		{
			matrix[i][j] = '-';
		}
	}
	printMatrix(matrix);

	matrix[2][3] = 'E';
	printMatrix(matrix);
	return 0;

}