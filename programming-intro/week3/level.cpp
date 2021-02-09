#include<iostream>
using namespace std;
int main(){
	int n=0;
	cin>>n;
	if(n>=90){
	cout<<"ÓÅ"<<endl; 
	} else if(n>=75){
		cout<<"Á¼"<<endl;
	} else if(n>=60){
		cout<<"ÖÐ"<<endl; 
	} else if(n<60)
	cout<<"²î"<<endl;	
	return 0;
}
