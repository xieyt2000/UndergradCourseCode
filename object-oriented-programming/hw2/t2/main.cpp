//(1)
#include"test.h"
/*Test F(Test &&a){
    Test b = a;
    return b;
}
int main(){
    Test A = F(1);
    cout<<endl;
    return 0;
}

(2)
Test&& F(Test &a){
    Test b = a;
    return std::move(b);
}
int main(){
    Test tmp;
    Test A = F(tmp);
    return 0;
}
//(3)
const Test& F(const Test& a){
    Test b = a;
    return std::move(b);
}
int main() {
    Test a;
    const Test &A = F(std::move(a));
    return 0;
}


//(4)
Test F(const Test& a){
    Test b = std::move(a); 
    return b;
}
int main(){
    Test A = F(1);
    cout<<endl;
    return 0;
}
*/ 

//£¨5£© 
const Test& F(Test a){
    Test& b = a;
    return b;
}
int main(){
    Test a;
    Test A = F(a);
    cout<<*(A.buf);
    return 0;
}
