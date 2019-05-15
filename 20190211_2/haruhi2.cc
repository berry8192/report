#include <iostream>
#include <vector>
#include <time.h>

std::vector<int> l;

int factorial(int n){

	int x=n;

	while(n>2){
		x*=n-1;
		n--;
	}

	return x;
}

void gen_l(int size){

	l.resize(size);
	l[0]=1;

	for(int i=1;i<size;i++){
		if(i%2==1) l[i]=1;
		if(i%2==0) l[i]=1;
	}

}

int check_P(int m, int n, int x){

	int count=1;
	int flag;
	std::vector<int> exist(n);
	std::vector<int> check(m*n);
	check[0]=0;

	for(int k=0;k<x-n+1;k++){
		for(int i=0;i<n;i++) exist[i]=0;
		for(int j=0;j<count;j++){
			flag=0;
			for(int i=0;i<n;i++){
				exist[l[k+i]-1]=1;
				if(check[j*n+i]!=l[k+i]){
					flag=1;
				}
			}
			if(flag==0) break;
		}
		if(flag==1){
			for(int i=0;i<n;i++) flag*=exist[i];
			if(flag==1){
				for(int i=0;i<n;i++) check[count*n+i]=l[k+i];
				count++;
				if(count==m+1) return 1;
			}
		}
	}

	return 0;
}

int fix_one(int n, int size){

	for(int i=size-1;i>=0;i--){
		if(i==0) return 1;
		if(l[i]!=n){
			l[i]++;
			break;
		}
		l[i]=1;
	}
	return 0;
}

int main(){

	int x=1;
	int flag=0;
	int n, m;
   	clock_t start, end;

	std::cin >> n;
	m=factorial(n);
	std::cout << n << "!=" << m << "\n";

	start=0.;
	while(1){
		if(start!=0.){
			end=clock();
			std::cout << "check" << x-1 << " time is " << end-start << "\n";
		}
		start=clock();

		gen_l(x);
		do{
			if(check_P(m, n, x)==1){
				std::cout << "clear\n";
				for(int i=0;i<x;i++) std::cout << l[i];
				flag=1;
				break;
			}
		} while(fix_one(n, x)==0);

		if(flag==1) break;
		x++;
	}

	std::cout << " is shortest (length is " << x << ")\n";
}
