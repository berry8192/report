#define PLIST 22
#define POS 6

#include <stdio.h>
#include <stdlib.h>

struct position{
  int x;
  int y;
};

struct path_list{
  int can;
  //int pos_number;
  struct position pos[POS];
  };

struct number{
  int distance;
  int path_number;
  struct position spos;
  struct position npos;
  struct position gpos;
  struct path_list plist[PLIST];
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
  int i, j, k;
  int tmp=0;
  
  //set spos, gpos
  for(i=1;i<=size;i++){
    num[i].spos=cboard[i];
    num[i].npos=cboard[i];
    num[i].gpos=cboard[i];
    num[i].path_number=0;
    
    for(j=0;j<PLIST;j++){
      num[i].plist[j].can=0;
      for(k=0;k<POS;k++){
	num[i].plist[j].pos[k].x=-1;
	num[i].plist[j].pos[k].y=-1;
      }
    }
    //printf("pos reset");
    //num[i].plist[0].pos_number=0;
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
}

int dir(struct number *num, struct position *cboard, int **board, int step, int sizex, int sizey){
  int i, j, k, xdis, ydis;
  int flag=0;

  if(step<0) return 0;
  
  //printf("\ndir in\n");

  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(i==0 && j==0) continue;

      //printf("i=%d j=%d step=%d\n",i ,j ,step);
      //printf("spos(%d, %d) npos(%d, %d)->",num->spos.x ,num->spos.y ,num->npos.x ,num->npos.y);
      
      num->npos.x+=i;
      num->npos.y+=j;

      //printf("npos(%d, %d) gpos(%d, %d)\n",num->npos.x ,num->npos.y ,num->gpos.x ,num->gpos.y);

      //printf("into %d-%d\n",num->path_number ,num->distance - step);
	
      //goal
      if(num->npos.x==num->gpos.x && num->npos.y==num->gpos.y && step==0){
	
	//twice check
	if(2 <= num->distance - step){
	  for(k=0;k <= num->distance - step - 2;k++){
	    //printf("%dpos=(%d, %d) %dpos=(%d, %d)\n",num->distance - step ,num->npos.x ,num->npos.y, k, num->plist[num->path_number].pos[k].x, num->plist[num->path_number].pos[k].y);
	    if(num->npos.x == num->plist[num->path_number].pos[k].x && num->npos.y == num->plist[num->path_number].pos[k].y) flag=1;
	  }
	}
	if(flag==1){
	  flag=0;
	  //printf(" %d(%d, %d) twice\n", board[num->spos.y][num->spos.x], num->spos.x, num->spos.y);
	  num->npos.x-=i;
	  num->npos.y-=j;
	  continue;
	}

	num->plist[num->path_number].can=1;
	  
	num->path_number++;
	
	//umeru
	for(k=0;k<=num->distance;k++){
	  num->plist[num->path_number].pos[k].x=num->plist[num->path_number - 1].pos[k].x;
	  num->plist[num->path_number].pos[k].y=num->plist[num->path_number - 1].pos[k].y;
	}
	
	//num->plist=(struct path_list*)realloc(num->plist, sizeof(struct path_list));
	//printf("goal\n\n\n");
	
	//num->plist[num->path_number].pos_number--;
	num->npos.x-=i;
	num->npos.y-=j;
	continue;
	
      }else{
	//bounce check
	if(num->npos.x<0 || sizey<=num->npos.x || num->npos.y<0 || sizex<=num->npos.y){	
	  num->npos.x-=i;
	  num->npos.y-=j;
	  //printf(" out of bounce\n");
	  continue;
	}
	
	//printf("npos=%d\n",board[num->npos.y][num->npos.x]);

	//blank check
	if(board[num->npos.y][num->npos.x]==0){

	  //impossioble check
	  if(num->gpos.x <= num->npos.x){
	    xdis=num->npos.x - num->gpos.x;
	  }else{
	    xdis=num->gpos.x - num->npos.x;
	  }
	  if(num->gpos.y <= num->npos.y){
	    ydis=num->npos.y - num->gpos.y;
	  }else{
	    ydis=num->gpos.y - num->npos.y;
	  }
	  if(step<xdis || step<ydis){
	    num->npos.x-=i;
	    num->npos.y-=j;
	    //printf(" imposible\n");
	    continue;
	  }

	//twice check
	if(2 <= num->distance - step){
	  //printf("\n\n");
	  for(k=0;k <= num->distance - step - 2;k++){
	    //printf("%dpos=(%d, %d) %dpos=(%d, %d)\n",num->distance - step ,num->npos.x ,num->npos.y, k, num->plist[num->path_number].pos[k].x, num->plist[num->path_number].pos[k].y);
	    if(num->npos.x == num->plist[num->path_number].pos[k].x && num->npos.y == num->plist[num->path_number].pos[k].y) flag=1;
	  }
	  //printf("\n\n");
	}
	if(flag==1){
	  flag=0;
	  //printf(" %d(%d, %d) twice\n", board[num->spos.y][num->spos.x], num->spos.x, num->spos.y);
	  num->npos.x-=i;
	  num->npos.y-=j;
	  continue;
	}
	  
	//printf(" call\n");
	  num->plist[num->path_number].pos[num->distance - step].x=num->npos.x;
	  num->plist[num->path_number].pos[num->distance - step].y=num->npos.y;
	  //num->plist[num->path_number].pos=(struct position*)realloc(num->plist[num->path_number].pos, sizeof(struct position));
	  //num->plist[num->path_number].pos_number++;
	  dir(*&num, cboard, board, step-1, sizex, sizey);
	  
	}else{
	  num->npos.x-=i;
	  num->npos.y-=j;
	  //printf(" not blank\n");
	  continue;
	}
	num->npos.x-=i;
	num->npos.y-=j;
      }
    }
  }
}

int path_dec(struct number *num, int **board, int size){
  int i, j, k, flag;
  int dec=0;

  for(i=1;i<=size;i++){
    if(1 <= num[i].distance){
      for(j=0;j<PLIST;j++){
	flag=0;
	
	if(num[i].plist[j].can==1){
	  for(k=0;k < num[i].distance;k++){
	    if(board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]!=0){
	      flag=1;
	    }
	  }
	}
	
	if(flag==1){
	  flag=0;
	  num[i].plist[j].can=0;
	  num[i].path_number--;
	  printf("dec num[%d].plist[%d].pos[k]=%d\n",i,j,k,num[i].path_number);
	  dec=1;
	  
	}
      }
    }
  }

  for(i=1;i<=size;i++){
    if(num[i].path_number==1){
      for(j=0;j<PLIST;j++){
	if(num[i].plist[j].can==1){
	  for(k=0;k<num[i].distance;k++){
	    board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]=i+k+1;
	    printf("umeru\n");
	  }
	  num[i].distance=-1;
	}
      }
    }
  }

  return dec;
  
}

int blank_ume(struct number *num, int **board, int sizex, int sizey){
  int i, j, k;
  int flag=0;

  for(i=1;i<sizex;i++){
    for(j=1;j<sizey;j++){
      if(board[i][j]==0){
	
  
  
}

int main(int argc, char **argv){
  
  FILE *fp;
  int i, j, k, size, sizex, sizey;
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

  //for(i=76;i<=76;i++){
  for(i=1;i<=sizex*sizey;i++){
    /*//malloc num.plist.pos
    for(j=0;j<num[i].distance;j++){
      num[i].plist[j].pos=(struct position*)malloc(sizeof(struct position) * num[i].distance);
    }
    */
    if(num[i].distance<1) continue;
    dir(&num[i], cboard, board, num[i].distance, sizex, sizey);
    if(num[i].path_number==1){
      printf(" %d\n",i);
      for(j=0;j<num[i].distance;j++){
	printf("%d %d\n",num[i].plist[0].pos[j].x, num[i].plist[0].pos[j].y);
	board[num[i].plist[0].pos[j].y][num[i].plist[0].pos[j].x]=i+j+1;
      }
      num[i].distance=-1;
    }
  }

  /*for(i=0;i<num[1].path_number;i++){
    for(j=0;j<num[1].plist[num[1].path_number].pos_number;j++){
      printf("(%d, %d) ",num[1].plist[i].pos[j].x ,num[1].plist[i].pos[j].x);
    }
    printf("\n");
  }*/

  //for(k=76;k<=76;k++){
  while(1){
  for(k=1;k<=sizex*sizey;k++){
    if(num[k].distance<1) continue;
    printf("%d\n",k);
    for(i=0;i<PLIST;i++){
      for(j=0;j<POS;j++){
	printf("(%d, %d) ",num[k].plist[i].pos[j].x ,num[k].plist[i].pos[j].y);
      }
      if(num[k].plist[i].can==1){
	printf("  can");
      }else{
	printf("  cannot");
      }
      printf("\n");
    }
    printf("%d\n",num[k].path_number);
    printf("\n");
    }
  
  //while(1){
    printf("\n");
    print_board(board, sizex, sizey);//check
    if(path_dec(&*num, &*board, sizex*sizey)==0 && blank_ume(&*num, &*board, sizex, sizey)==0){
      //printf("cannot slove\n");
      break;
    }
  }
  
  for (i=0;i<sizex;i++){
    free(board[i]);
  }
  free(board); 
  free(cboard);
  free(num);
  
  return 0;
}
