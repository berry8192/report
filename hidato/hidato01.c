#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  FILE *fp;
  int i, j, sizex, sizey;
  int **board;
  int *cboard;
  
  //undefined text file
  if (argc != 2) {
    return 1;
  }

  //reading error
  fp = fopen(argv[1], "r");
  if (fp ==NULL) {
    return 1;
  }
  
  //get board size
  fscanf(fp, "%d", &(sizex));
  fscanf(fp, "%d", &(sizey));
  printf("%d %d\n",sizex, sizey);

  //make boards
  board=malloc(sizeof(int *) * sizex);
  for(i=0;i<sizex;i++){
    board[i]=malloc(sizeof(int *) * sizey);
  }
  cboard=malloc(sizeof(int *) * sizex*sizey);

  //write
  for (i=0; i<sizex; i++) {
    for (j=0; j<sizey; j++) {
      fscanf(fp, "%d", &(board[i][j]));
    }
  }

  fclose(fp);

  for (i=0; i<sizex; i++) {
    for (j=0; j<sizey; j++) {
      printf("%2d ", board[i][j]);
    }
    printf("\n");
  }

  return 0;
}
