#include <iostream>
#include <vector>
#include <string>

#define NU 10
#define DE 1

int count;

class frac {
	public:
	int nu;
	int de;

	frac() {
	}

	frac(const int& x) {
		nu=x;
		de=1;
	}

	frac(const int& x, const int& y) {
		nu=x;
		de=y;
	}

	friend frac reduc(const frac& x) {
		int sma, big, tmp;

		if(x.nu < x.de) {
			sma=x.nu;
			big=x.de;

		} else if(x.de < x.nu) {
			sma=x.de;
			big=x.nu;

		} else {
			return frac(1);
		}

		if(sma==0) return frac(0, 1);

		while(1){
			tmp=big%sma;
			if (tmp==0) break;
			big=sma;
			sma=tmp;
		}

		if(x.nu<0) sma*=-1;

		return frac(x.nu/sma, x.de/sma);
	}

	friend frac operator+(const frac& x, const frac& y){
		frac z;

		z.nu = x.nu * y.de + x.de * y.nu;
		z.de = x.de * y.de;

		return reduc(z);
	}

	friend frac operator-(const frac& x, const frac& y){
		frac z;

		z.nu = x.nu * y.de - x.de * y.nu;
		z.de = x.de * y.de;

		return reduc(z);
	}

	friend frac operator*(const frac& x, const frac& y){
		frac z;

		z.nu = x.nu * y.nu;
		z.de = x.de * y.de;

		return reduc(z);
	}

	friend frac operator/(const frac& x, const frac& y){
		frac z;

		z.nu = x.nu * y.de;
		z.de = x.de * y.nu;

		return reduc(z);
	}
};

class num {
	public:
	frac fra;
	std::string str;

	num() {
	}

	num(const int& x) {
		fra=frac(x);
		str=std::to_string(x);
	}		

	friend num operator+(const num& x, const num& y){
		num z;

		z.fra = x.fra + y.fra;
		z.str = "(" + x.str + "+" + y.str + ")";

		return z;

	}

	friend num operator-(const num& x, const num& y){
		num z;

		z.fra = x.fra - y.fra;
		z.str = "(" + x.str + "-" + y.str + ")";

		return z;
	}

	friend num operator*(const num& x, const num& y){
		num z;

		z.fra = x.fra * y.fra;
		z.str = "(" + x.str + "*" + y.str + ")";

		return z;
	}

	friend num operator/(const num& x, const num& y){
		num z;

		z.fra = x.fra / y.fra;
		z.str = "(" + x.str + "/" + y.str + ")";

		return z;
	}

};

void set_n(std::vector<num>& n, std::string s){
	int len, mod, fig;

	len=s.size();
	fig = std::stoi(s);

	for(int i=0;i<len;i++){
		mod=fig%10;
		n.emplace_back(num(mod));
		fig=fig/10;
	}
}

void calc(std::vector<num> n){
	std::vector<num> n2;

	int len;

	len=n.size();

	if(len==1){
		if(n[0].fra.nu==NU && n[0].fra.de==DE){
			/*std::cout << n[0].str << "=" << NU;
			if(DE!=1) std::cout << "/" << DE;
			std::cout << "\n";*/
			count++;
		}
	return;
	}

	for(int i=0;i<len;i++){
		for(int j=i+1;j<len;j++){

			for(int k=0;k<len;k++){
				if(k!=i && k!=j){
					n2.emplace_back(n[k]);
				}
			}
			n2.emplace_back(n[i]+n[j]);
			calc(n2);
			n2.pop_back();

			n2.emplace_back(n[i]*n[j]);
			calc(n2);
			n2.pop_back();

			if(n[i].fra.nu!=0 && n[j].fra.nu!=0){
				n2.emplace_back(n[i]-n[j]);
				calc(n2);
				n2.pop_back();

				n2.emplace_back(n[j]-n[i]);
				calc(n2);
				n2.pop_back();
			}

			if(n[i].fra.nu!=0 && n[j].fra.nu!=0){
				if((n[j].fra.nu!=1 && n[j].fra.nu!=-1) || n[j].fra.de!=1){
					n2.emplace_back(n[i]/n[j]);
					calc(n2);
					n2.pop_back();
				}

				if((n[i].fra.nu!=1 && n[i].fra.nu!=-1) || n[i].fra.de!=1){
					n2.emplace_back(n[j]/n[i]);
					calc(n2);
					n2.pop_back();
				}
			}

			n2.clear();
		}
	}


}

int main(){
	std::vector<num> n;
	n.resize(4);
	count=0;

	//std::cin >> s;

	//set_n(n, s);

	for(int i=1; i<=9; i++){
		for(int j=i+1; j<=9; j++){
			for(int k=j+1; k<=9; k++){
				for(int l=k+1; l<=9; l++){
					n[0]=i;
					n[1]=j;
					n[2]=k;
					n[3]=l;
					calc(n);
					if(count==0) {
	std::cout << n[0].fra.nu << " " << n[1].fra.nu  << " " << n[2].fra.nu << " " << n[3].fra.nu << " "<< "NG\n";
	}else{
	std::cout << n[0].fra.nu << " " << n[1].fra.nu  << " " << n[2].fra.nu << " " << n[3].fra.nu << " " << "OK\n";
	}
					count=0;
				}
			}
		}
	}
}

