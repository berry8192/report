#include <iostream>

void print_board(int **board, int sizex, int sizey){
  
  int i, j;
  
  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      printf("%2d ", board[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char **argv){
  
  FILE *fp;
  int i, j, k, size, sizex, sizey;
  int **board;

  //undefined text file
  if (argc != 2){
    return 1;
  }

  //reading error
  fp = fopen(argv[1], "r");
  if (fp == NULL){
    return 1;
  }

  //get board size
  fscanf(fp, "%d", &(sizex));
  fscanf(fp, "%d", &(sizey));

}
