#include <stdio.h>
#include <stdlib.h>

struct position{
  int x;
  int y;
};

/*void set_start(struct number *num, struct position *cboard, int size){
  int i;
  int tmp=0;
  
  //set spos, gpos
  for(i=1;i<=size;i++){
    num[i].spos=cboard[i];
    num[i].gpos=cboard[i];
  }
  
  for(i=1;i<=size;i++){
    if(num[i].spos.x!=-1){
      num[tmp].gpos=num[i].spos;
      tmp=i;
    }else{
      num[tmp].gpos.x=-1;
      num[tmp].gpos.y=-1;
    }
  }
  
  for(i=1;i<=size;i++){
    printf("%d(%d, %d)->(%d, %d)\n",i, num[i].spos.x, num[i].spos.y, num[i].gpos.x, num[i].gpos.y);//check
    }
    }*/

void print_matrix_2d(int **a, int sizex, int sizey){
  int i, j;

  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      printf("%2d ", a[i][j]);
    }
    printf("\n");
  }
}

void malloc_check(int *a){
  if (a == NULL) {
    printf("no memory\n");
    abort();
    }
  printf("OK\n");//check
}

void malloc_check_2d(int **a){
  if (a == NULL) {
    printf("no memory\n");
    abort();
    }
  printf("OK\n");//check
  }


int main(int argc, char **argv){
  
  FILE *fp;
  int i, j, sizex, sizey;
  int **board;
  struct position *cboard;
  struct position *spos;
  struct position *gpos;
  struct position empty;
  empty.x=-1;
  empty.y=-1;
  
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
  printf("%d %d\n",sizex, sizey);//check
  
  //make board
  board=malloc(sizeof(int *) * sizex);
  for(i=0;i<sizex;i++){
    board[i]=malloc(sizeof(int) * sizey);
  }
  malloc_check_2d(board);

  //make cboard
  cboard=(struct position*)malloc(sizeof(struct position) * (sizex*sizey+1));
  for(i=1;i<=sizex*sizey;i++){
    cboard[i]=empty;
  }
  malloc_check(cboard);
  
  //make spos
  spos=(struct position*)malloc(sizeof(struct position) * (sizex*sizey+1));
  malloc_check(spos);
  
  //make gpos
  gpos=(struct position*)malloc(sizeof(struct position) * (sizex*sizey+1));
  malloc_check(gpos);

  //write to boards
  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      fscanf(fp, "%d", &(board[i][j]));
      if(board[i][j]!=0){
	cboard[board[i][j]].x=j;
	cboard[board[i][j]].y=i;
      }
    }
  }
  fclose(fp);

  print_matrix_2d(board, sizex, sizey);//check

  //set_start(&num, cboard, sizex*sizey);
  //while(1){
 
    //}

  for (i=0;i<sizex;i++){
    free(board[i]);
  }
  free(board); 
  free(spos);
  free(gpos);
  
  return 0;
}
