#include <stdio.h>
#include <stdlib.h>

struct position{
  int x;
  int y;
};

struct path_list{
  int can;
  struct position pos[1];
  };

struct number{
  int distance;
  int path_number;
  struct position spos;
  struct position gpos;
  struct path_list plist[1];
};

void print_board(int **board, int sizex, int sizey){
  
  int i, j;
  
  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      printf("%2d ", board[i][j]);
    }
    printf("\n");
  }
}

void set_start(struct number *num, struct position *cboard, int size){
  int i;
  int tmp=0;
  
  //set spos, gpos
  for(i=1;i<=size;i++){
    num[i].spos=cboard[i];
    num[i].gpos=cboard[i];
    num[i].path_number=0;
  }
  
  for(i=1;i<=size;i++){
    if(num[i].spos.x!=-1){
      num[tmp].gpos=num[i].spos;
      num[tmp].distance=i-tmp-1;
      tmp=i;
      
    }else{
      num[tmp].gpos.x=-1;
      num[tmp].gpos.y=-1;
      num[i].distance=-1;
    }
  }
  
  for(i=1;i<=size;i++){
    printf("%d(%d, %d)->(%d, %d) %d\n",i, num[i].spos.x, num[i].spos.y, num[i].gpos.x, num[i].gpos.y, num[i].distance);//check
    }
}

void path(struct number *num, int size){
  int i;
  
  for(i=1;i<=size;i++){
    //num[i].
  }
}
struct position dir(struct number *num, struct position *cboard, int **board, int size){
  int i, j;

  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(i==0 && j==0) continue;
      if(num.spos.x+i==num.gpos.x && num.spos.y+j==num.gpos.y){
      }
      if(board[num.spos.x+i][num.spos.y+j]==0){
	num.plist[path_number].pos[].x=num.spos.x+i;
	num.plist[path_number].pos[].y=num.spos.y+j;
      }
      
      num[k].distance--;
      dir(&*num, cboard, board);
    }
  }

}

int main(int argc, char **argv){
  
  FILE *fp;
  int i, j, size, sizex, sizey;
  int **board;
  struct position *cboard;
  struct number *num;
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

  //size=(int*)sizeof(struct number);
  //printf("%d\n",size);
  //write to boards
  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      fscanf(fp, "%d", &(board[i][j]));
      if(board[i][j]!=0){
	cboard[board[i][j]].x=j;
	cboard[board[i][j]].y=i;
	//printf("(%d, %d)=%d\n",i,j,board[i][j]);
      }
    }
  }
  fclose(fp);

  //make number struct
  num=(struct number*)malloc(sizeof(struct number) * (sizex*sizey+1));
  if (num == NULL) abort();

  print_board(board, sizex, sizey);//check

  set_start(&*num, cboard, sizex*sizey);
  for(i=1;i<=sizex*sizey;i++){
    //path(&*num, sizex*sizey);
  }
  
  //while(1){
 
    //}
  
  for (i=0;i<sizex;i++){
    free(board[i]);
  }
  free(board); 
  free(cboard);
  free(num);
  
  return 0;
}
