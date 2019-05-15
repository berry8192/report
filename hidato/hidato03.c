#include <stdio.h>
#include <stdlib.h>

void print_board(int **board, int sizex, int sizey)
{
  int i, j;
  
  for (i=0; i<sizex; i++) {
    for (j=0; j<sizey; j++) {
      printf("%2d ", board[i][j]);
    }
    printf("\n");
  }
}

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

  //make board
  board=malloc(sizeof(int *) * sizex);
  for(i=0;i<sizex;i++){
    board[i]=malloc(sizeof(int *) * sizey);
  }

  //make cboard
  cboard=malloc(sizeof(int *) * sizex*sizey+1);
  for(i=0;i<sizex*sizey+1;i++){
    cboard[i]=0;
  }

  //write to boards
  for (i=0; i<sizex; i++) {
    for (j=0; j<sizey; j++) {
      fscanf(fp, "%d", &(board[i][j]));
      if(board[i][j]!=0) cboard[board[i][j]]=1;
    }
  }
  fclose(fp);

  print_board(board, sizex, sizey);

  for(i=0;i<sizex*sizey+1;i++){
    printf("%d",cboard[i]);
  }

  free(board);
  free(cboard);
  
  return 0;
}
