#include <stdio.h>

int board[8][8];

int main(int argc, char **argv)
{
	FILE *fp;
	int i, j;

	if (argc != 2) {
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp ==NULL) {
		return 1;
	}

	for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
			fscanf(fp, "%d", &(board[i][j]));
		}
	}

	for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}

	return 0;
}
