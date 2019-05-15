#define VOLT 5

#include <math.h>
#include "matrix.h"

int gauss(double **a, double *b, int n)
{
    int i, j, k;
    double tmp;
    int p_num;
    double p_max;

    for (k=0; k<n-1; k++) {
        p_num = -1;
        p_max = 0.;
        for (i=k; i<n; i++) {
            tmp = fabs(a[i][k]);
            if (tmp > p_max) {
                p_max = tmp;
                p_num = i;
            }
        }
        if (p_num == -1) {
            return 0;
        }

        for (i=k; i<n; i++) {
            tmp = a[k][i];
            a[k][i] = a[p_num][i];
            a[p_num][i] = tmp;
        }
        tmp = b[k];
        b[k] = b[p_num];
        b[p_num] = tmp;

        for (i=k+1; i<n; i++) {
            tmp = a[i][k] / a[k][k];
            for (j=k; j<n; j++) {
                a[i][j] -= a[k][j] * tmp;
            }
            b[i] -= b[k] * tmp;
        }
    }

    if (a[n-1][n-1] == 0) return 0;

    for (i = n-1; i>=0; i--) {
        for (j = i+1; j<n; j++) {
            b[i] -= a[i][j] * b[j];
        }
        b[i] /= a[i][i];
    }

    return 1;
}

int main(int argc, char **argv)
{
  FILE *fp;
  int sizex, sizey, count, tmp, i, j, k, l, n, start, end;
  int **board;
  double **a;
  double *b;

  count=0;

  //text file is not defined
  if (argc != 2){
    return 1;
  }
  
  //reading error
  fp = fopen(argv[1], "r");
  if (fp == NULL){
    return 1;
  }

  //get board size from text file
  fscanf(fp, "%d", &(sizey));
  fscanf(fp, "%d", &(sizex));

  //make board
  board = alloc_matrix_int(sizex+2, sizey+2);
  if (board == NULL) abort();
  
  //set -1 to board
  for (i=0; i<sizey+2; i++){
    for (j=0; j<sizex+2; j++){
      board[j][i]=-1;
    }
  }
  
  //write to board
  for (i=1; i<sizey+1; i++){
    for (j=1; j<sizex+1; j++){
      fscanf(fp, "%d", &tmp);
      if(0<tmp){
	
	if(tmp==2) start=count;//find start
	if(tmp==3) end=count;//find end
	
	board[j][i]=count;
	count++;
      }
    }
  }

  //make a, b
  a = alloc_matrix(count, count);
  b = alloc_vector(count);
  if (a == NULL) abort();
  if (b == NULL) abort();

  //set 0 to a, b
  for(i=0;i<sizey;i++){
    for(j=0;j<sizey;j++){
      a[j][i]=0;
    }
    b[i]=0;
  }

  //write to a
  for(i=1;i<sizey+2;i++){
    for(j=1;j<sizex+2;j++){
      
      if(board[j][i]!=-1){
	
	for(k=-1;k<=1;k++){
	  for(l=-1;l<=1;l++){
	    
	    if(l+k==1 || l+k==-1){
	      
	      if(board[j+l][i+k]>=0){
		a[board[j][i]][board[j][i]]+=1.0;
		a[board[j][i]][board[j+l][i+k]]-=1.0;
	      }
	    }
	  }
	}
      }
    }
  }

  //set start, end 
  for(i=0;i<count;i++){
    if(i==start){
      a[start][i]=1;
    }else{
      a[start][i]=0;
    }
    if(i==end){
      a[end][i]=1;
    }else{
      a[end][i]=0;
    }
  }

  //write to b
  b[start]=VOLT;

  //gauss
  gauss(a, b, count);

  //print
  print_vector(b, count);

  //free
  free_matrix(a);
  free_matrix_int(board);
  free_vector(b);

  return 0;
}
