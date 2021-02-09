#include<iostream>
#include<string.h>
using namespace std;
char * sum(char * a, char * b){
	char*c=new char[109];
	int la=strlen(a), lb=strlen(b);
	for(int ia=la-1,ib=lb-1,ic=0;ia>=0){
		int da=a[ia]-'0';
		int db=b[ib]-'0';
		int res=da+db+dc;
		c[ic]=char(res+'0')
	}
	return c;
}
int main(){
	char a[109], b[109];
	cin>>a>>b;
	cout<<sum(a,b)<<endl;
	return 0;
}
