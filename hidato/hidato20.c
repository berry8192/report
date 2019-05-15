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
  
  //set 0
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
    //num[i].plist[0].pos_number=0;
  }

  //set distance
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

void undo_pos(struct number *num, int i, int j){
    num->npos.x-=i;
    num->npos.y-=j;
}  

int twice_check(struct number *num, int step){
  int k;
  
  if(2 <= num->distance - step){
    for(k=0;k <= num->distance - step - 2;k++){
      //printf("%dpos=(%d, %d) %dpos=(%d, %d)\n",num->distance - step ,num->npos.x ,num->npos.y, k, num->plist[num->path_number].pos[k].x, num->plist[num->path_number].pos[k].y);
      if(num->npos.x == num->plist[num->path_number].pos[k].x && num->npos.y == num->plist[num->path_number].pos[k].y) return 1;
    }
  }
  return 0;
}

void copy_plist(struct number *num){
  int k;
  
  //num->plist=(struct path_list*)realloc(num->plist, sizeof(struct path_list));
  
  for(k=0;k<=num->distance;k++){
    num->plist[num->path_number].pos[k].x=num->plist[num->path_number - 1].pos[k].x;
    num->plist[num->path_number].pos[k].y=num->plist[num->path_number - 1].pos[k].y;
	}
}

int far_check(struct number *num, int step, int *xdis, int *ydis){
  
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
    return 1;
  }else{
    return 0;
  }
}

int dir(struct number *num, int **board, int step, int sizex, int sizey){
  int i, j, k, xdis, ydis;

  if(step<0) return 0;
  
  //printf("\ndir in\n");
  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(i==0 && j==0) continue;      
      num->npos.x+=i;
      num->npos.y+=j;
	
      //goal
      if(num->npos.x==num->gpos.x && num->npos.y==num->gpos.y && step==0){
	
	//twice check
	if(twice_check(num, step)==1){
	  undo_pos(&*num, i, j);
	  continue;
	}

	num->plist[num->path_number].can=1;
	num->path_number++;
	
	//copy plist
	copy_plist(&*num);
	
	//printf("goal\n\n\n");
	
	//num->plist[num->path_number].pos_number--;
	undo_pos(&*num, i, j);
	continue;
	
      }else{
	//bounce check
	if(num->npos.x<0 || sizey<=num->npos.x || num->npos.y<0 || sizex<=num->npos.y){
	  undo_pos(&*num, i, j);
	  continue;
	}

	//blank check
	if(board[num->npos.y][num->npos.x]!=0){
	  undo_pos(&*num, i, j);
	  continue;
	}

	//impossioble check
	if(far_check(num, step, &xdis, &ydis)==1){
	  undo_pos(&*num, i, j);
	  continue;
	}

	//twice check
	if(twice_check(num, step)==1){
	  undo_pos(&*num, i, j);
	  continue;
	}
	  
	//printf(" call\n");
	num->plist[num->path_number].pos[num->distance - step]=num->npos;
	
	//num->plist[num->path_number].pos=(struct position*)realloc(num->plist[num->path_number].pos, sizeof(struct position));
	//num->plist[num->path_number].pos_number++;
	dir(*&num, board, step-1, sizex, sizey);

	undo_pos(&*num, i, j);
      }
    }
  }
}

int path_dec(struct number *num, int **board, struct position *cboard, int size){
  int i, j, k, flag;
  int dec=0;

  for(i=1;i<=size;i++){
    if(1 <= num[i].distance){
      for(j=0;j<num[i].path_number;j++){
	flag=0;
	
	if(num[i].plist[j].can==1){
	  for(k=0;k < num[i].distance;k++){
	    printf("num[%d].plist[%d].pos[%d] value=%d path(%d, %d) cboard(%d, %d)\n",i,j,k,board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x], num[i].plist[j].pos[k].x, num[i].plist[j].pos[k].y, cboard[board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]].x, cboard[board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]].y);
	    
	    /*if(num[i].plist[j].pos[k].x!=cboard[board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]].x || num[i].plist[j].pos[k].y!=cboard[board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]].y){
	      if(board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]!=0){
		flag=1;
		printf("%d\n", board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]);
	      }
	      }*/
	    
	    //if(cboard[board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]].x==-1){
	    if(cboard[i+k+1].x==-1){
	      printf("cboard dont exist\n");
	      if(board[num[i].plist[j].pos[k].y][num[i].plist[j].pos[k].x]!=0){
		printf("flag!!!!!!!!!!!\n");
		flag=1;
	      }else{
		printf("else\n");
	      }
	    }else{
	      printf("cboard exist\n");
	      if(num[i].plist[j].pos[k].x!=cboard[i+k+1].x || num[i].plist[j].pos[k].y!=cboard[i+k+1].y){
		flag=1;
		printf("flag!!!!!!!!!!!\n");
	      }else{
		printf("else\n");
	      }
	    }
	    
	  }
	}
	
	if(flag==1){
	  flag=0;
	  for(k=0;k<PLIST;k++){
	    if(num[i].plist[k].can==0){
	      num[i].plist[j]=num[i].plist[k-1];
	      k+=PLIST;
	    }
	  }
	  k-=PLIST;
	  num[i].plist[k-2].can=0;
	  num[i].path_number--;
	  printf("dec num[%d].plist[%d]=%d\n",i,j,num[i].path_number);
	  dec=1;
	  
	}
      }
    }
  }

  for(i=1;i<=size;i++){
    if(num[i].path_number==1){
      for(j=0;j<num[i].distance;j++){
	board[num[i].plist[0].pos[j].y][num[i].plist[0].pos[j].x]=i+j+1;
	cboard[i+j+1]=num[i].plist[0].pos[j];
	printf("umeru (%d, %d)=%d\n",num[i].plist[0].pos[j].x ,num[i].plist[0].pos[j].y, i+j+1);
      }
      num[i].distance=-1;
    }
  }

  return dec;
  
}

int blank_ume(struct number *num, int **board, struct position *cboard, int sizex, int sizey){
  int i, j, k, l, m, tmp;
  int flag=0;
  int ume=0;

  for(i=0;i<sizex;i++){
    for(j=0;j<sizey;j++){	     
      if(board[i][j]==0){
	//printf("\ncheck board[%d][%d]\n",j,i);
	flag=0;
	tmp=-1;

	for(k=1;k<=sizex*sizey;k++){
	  //printf("k%d ",k);
	  if(1<=num[k].distance){
	    for(l=0;l<num[k].path_number;l++){
	      //printf("l%d ",l);
	      if(num[k].plist[l].can==1){
		for(m=0;m<num[k].distance;m++){
		  //printf("m%d ",m);
		  //printf("check(%d, %d)\n",num[k].plist[l].pos[m].x,num[k].plist[l].pos[m].y);
		  if(num[k].plist[l].pos[m].x==j && num[k].plist[l].pos[m].y==i){
		    //printf("board[%d][%d] num[%d].plist[%d].pos[%d] flag=%d tmp=%d\n",j,i,k,l,m,flag,tmp);
		    
		    if((flag==2 || tmp!=k+m+1) && tmp!=-1){
		      //printf("second %d %d\n",flag, k+m+1);
		      flag=-1;
		      k+=sizex*sizey;
		      l+=num[k].path_number;
		      m+=num[k].distance+1;
		    }else{
		      //printf("first/same\n");
		      flag=1;
		      tmp=k+m+1;
		    }
		    
		  }
		}
	      }
	    }
	  }
	      
	  if(flag==1){
	    flag=2;
	  }
	      
	}
	  
	if(flag==2){
	  printf("board[%d][%d]=%d ume\n",j,i,tmp);
	  board[i][j]=tmp;
	  cboard[tmp].x=j;
	  cboard[tmp].y=i;
	  ume=1;
	  l+=sizex*sizey;
	  k+=num[k].path_number;
	}
	    
      }
    }
  }	
    return ume;
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
  for(i=0;i<=sizex*sizey;i++){
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
    dir(&num[i], board, num[i].distance, sizex, sizey);
    if(num[i].path_number==1){
      printf(" %d\n",i);
      for(j=0;j<num[i].distance;j++){
	printf("%d %d\n",num[i].plist[0].pos[j].x, num[i].plist[0].pos[j].y);
	board[num[i].plist[0].pos[j].y][num[i].plist[0].pos[j].x]=i+j+1;
	cboard[i+j+1]=num[i].plist[0].pos[j];
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
    for(i=1;i<=sizex*sizey;i++){
      printf("%d(%d, %d) ", i, cboard[i].x, cboard[i].y);
    }
    printf("\n");
    if(path_dec(&*num, &*board, &*cboard, sizex*sizey)==0){
      if(blank_ume(&*num, &*board, &*cboard, sizex, sizey)==0){
	//printf("cannot slove\n");
	break;
      }
    }
  }
    print_board(board, sizex, sizey);//check
  
  for (i=0;i<sizex;i++){
    free(board[i]);
  }
  free(board); 
  free(cboard);
  free(num);
  
  return 0;
}
