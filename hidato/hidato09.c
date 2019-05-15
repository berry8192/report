#include <stdio.h>
#include <stdlib.h>

struct position{
  int x;
  int y;
};

void set_spos(struct position *spos, struct position *cboard, int size){
  int i;
  
  for(i=1;i<=size;i++){
    spos[i]=cboard[i];
    //printf("%d\n",spos[i].x ,spos[i].y);
  }
}

void set_gpos(struct position *gpos, struct position *spos, int size){
  int i;
  int tmp=0;
  
  for(i=1;i<=size;i++){
    if(spos[i].x!=-1){
      gpos[tmp]=spos[i];
      tmp=i;
    }else{
      gpos[tmp].x=-1;
      gpos[tmp].y=-1;
    }
  }
  
  for(i=1;i<=size;i++){
    printf("%d(%d, %d)->(%d, %d)\n",i ,spos[i].x ,spos[i].y ,gpos[i].x ,gpos[i].y);//check
  }
}

void print_matrix_2d(int **a, int sizex, int sizey){
  int i, j;

  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      printf("%2d ", a[i][j]);
    }
    printf("\n");
  }
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
  if (board == NULL) abort();
 
  //make cboard
  cboard=(struct position*)malloc(sizeof(struct position) * (sizex*sizey+1));
  for(i=1;i<=sizex*sizey;i++){
    cboard[i]=empty;
  }
  if (cboard == NULL) abort();
  
  //make spos
  spos=(struct position*)malloc(sizeof(struct position) * (sizex*sizey+1));
  for(i=1;i<=sizex*sizey;i++){
    //spos[i]=empty;
  }
  if (spos == NULL) abort();
  
  //make gpos
  gpos=(struct position*)malloc(sizeof(struct position) * (sizex*sizey+1));
  for(i=1;i<=sizex*sizey;i++){
    //gpos[i]=empty;
  }
  if (gpos == NULL) abort();

  //write to boards
  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      fscanf(fp, "%d", &(board[i][j]));
      if(board[i][j]!=0){
	cboard[board[i][j]].x=j;
	cboard[board[i][j]].y=i;
	//printf("%d, %d\n",cboard[board[i][j]].x ,cboard[board[i][j]].y);
      }
    }
  }
  fclose(fp);

  print_matrix_2d(board, sizex, sizey);//check

  set_spos(&*spos, cboard, sizex*sizey);
  set_gpos(&*gpos, spos, sizex*sizey);
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
