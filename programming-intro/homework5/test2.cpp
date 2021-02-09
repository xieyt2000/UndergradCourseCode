#include<iostream>
#include<string.h>
using namespace std;
char text[100],code[100];
void Encrptchar(char x[100]){
	int len=strlen(x);
	for(int i=0;i<=len;i++){
		code[i]=x[i];
		
		}		
	}	

int main(){
	cin>>text;
	Encrptchar(text);
	cout<<code<<endl;
	return 0;
}
