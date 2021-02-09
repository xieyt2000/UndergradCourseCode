#include<iostream>
#include<string.h>
using namespace std;
char text[100],code[100];
void Encrptchar(char x[100]){
	int len=strlen(x);
	for(int i=0;i<=len;i++){
		code[i]=x[i];
		if(x[i]=='z'||x[i]=='Z'){
		code[i]=x[i]-25;	
		}
		if((64<x[i]&&x[i]<91)||(96<x[i]&&x[i]<123)){
			code[i]=x[i]+1;
		}		
	}	
}
int main(){
	cin>>text;
	Encrptchar(text);
	cout<<code<<endl;
	return 0;
}
