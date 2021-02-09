#include<iostream>
#include<string.h>
using namespace std;
char a[20], b[20], c[20], d[20];
int A, B;
int main(){
	cin>>a>>b;
	A=strlen(a);
	B=strlen(b);
	if(A!=B) cout<<1;
	else{
		if(!strcmp(a,b)) cout<<2;
		else{
			for(int i=0;i<A;i++){
				if(a[i]>'Z'){
					a[i]=a[i]-32;
				}
			}
			for(int i=0;i<B;i++){
				if(b[i]>'Z'){
					b[i]=b[i]-32;
				}
			}
			if(!strcmp(a,b)) cout<<3;
			else cout<<4;			
		}
	}	
	cout<<endl;
	return 0;
}
