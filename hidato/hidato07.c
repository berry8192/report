#include <stdio.h>
#include <stdlib.h>

struct position{
  int x;
  int y;
};

/*struct path_list{
  int can;
  struct position pos[];
  };*/

struct number{
  int distance;
  int path_decide;
  struct position spos;
  struct position gpos;
  //struct path_list plist[];
};

void set_start(struct number **num, struct position *cboard, int size){
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
    //printf("%d(%d, %d)\n",i, num[i].spos.x, num[i].spos.y);//check
    //printf("%d,%d\n",num[tmp].gpos.x, num[tmp].gpos.y);
    //printf("%d(%d, %d)->\n",i, num[i].spos.x, num[i].spos.y);
    }
}

void print_board(int **board, int sizex, int sizey){
  
  int i, j;
  
  for (i=0; i<sizex; i++){
    for (j=0; j<sizey; j++){
      printf("%2d ", board[i][j]);
    }
    printf("\n");
  }
}

int malloc_check(int *a){
  if (a == NULL) {
    printf("no memory\n");
    return 1;
    }
  printf("OK\n");//check
  return 0;
}

int malloc_check2(int **a){
  if (a == NULL) {
    printf("no memory\n");
    return 1;
    }
  printf("OK\n");//check
  return 0;
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
  if(malloc_check2(board)==1) return 1;

  //make cboard
  cboard=(struct position*)malloc(sizeof(struct position) * (sizex*sizey+1));
  for(i=1;i<=sizex*sizey;i++){
    cboard[i]=empty;
  }
  if(malloc_check(cboard)==1) return 1;

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
  if(malloc_check(num)==1) return 1;

  print_board(board, sizex, sizey);//check

  set_start(&num, cboard, sizex*sizey);
  //while(1){
 
    //}

  free(board);
  free(cboard);
  free(num);
  
  return 0;
}
