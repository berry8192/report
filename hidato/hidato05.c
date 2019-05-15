#include <stdio.h>
#include <stdlib.h>

struct position {
  int x;
  int y;
};

struct path_list {
  int can;
  struct position pos[];
};

struct number {
  int distance;
  int path_decide;
  struct position spos;
  struct position gpos;
  struct path_list plist[];
};

void set_number(struct number *num, struct position *cboard, int size) {
  int i;
  for(i=1;i<size;i++){
    num[i].spos=cboard[i];
    printf("(x,y)=%d, %d\n",num[i].spos.x, num[i].spos.y);
  }
}

void path(struct number *num) {

}

void print_board(int **board, int sizex, int sizey) {
  
  int i, j;
  
  for (i=0; i<sizex; i++) {
    for (j=0; j<sizey; j++) {
      printf("%2d ", board[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
  
  FILE *fp;
  int i, j, sizex, sizey;
  int **board;
  struct position *cboard;
  struct number *num;
  struct position zero;
  zero.x=0;
  zero.y=0;
  
  //undefined text file
  if (argc != 2) {
    return 1;
  }

  //reading error
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    return 1;
  }
  
  //get board size
  fscanf(fp, "%d", &(sizex));
  fscanf(fp, "%d", &(sizey));
  printf("%d %d\n",sizex, sizey);//check
  
  //make board
  board=malloc(sizeof(int *) * sizex);
  for(i=0;i<sizex;i++){
    board[i]=malloc(sizeof(int *) * sizey);
  }

  //make cboard
  cboard=malloc(sizeof(int *) * sizex*sizey+1);
  for(i=1;i<sizex*sizey+1;i++){
    cboard[i]=zero;
  }

  //write to boards
  for (i=0; i<sizex; i++) {
    for (j=0; j<sizey; j++) {
      fscanf(fp, "%d", &(board[i][j]));
      if(board[i][j]!=0) {
	cboard[board[i][j]].x=i;
	cboard[board[i][j]].y=j;
      }
    }
  }
  fclose(fp);

  //make number struct
  num=malloc(sizeof(struct number *) * sizex*sizey+1);

  print_board(board, sizex, sizey);//check

  //while(1){
    set_number(&num, cboard, sizex*sizey);
    //path(&num);

 
    //}

  for(i=0;i<sizex*sizey+1;i++){
    printf("%d",cboard[i]);//check
  }

  free(board);
  free(cboard);
  free(num);
  
  return 0;
}
