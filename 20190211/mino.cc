#include <iostream>

#define SIZE 4
int board[SIZE][SIZE];

void print_board(void){

  for (int i=0; i<SIZE; i++){
    for (int j=0; j<SIZE; j++){
      printf("%d", board[i][j]);
    }
    printf("\n");
  }
}

int main(){

	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			board[i][j]=1;
		}
	}

	print_board();

}
